const { exec } = require('child_process');

module.exports = async function entry(data) {

    // const filterErrors = output => output.join('').split('\n').filter(i => /^[a-zA-Z]:\\.+(\\.+)*\(\d+\): error.*/.test(i)).join('\n').trim();
    const filterErrors = output => output.join('').split('\n').filter(i => /^[a-zA-Z]:\\|\/.* :\s*error\s*:/.test(i)).map(i => i.trim()).join('\n').trim();

    // const clean = await proc(`clean`);
    // if (taskComplete(clean.success, "clean", clean.output)) return -1;

    console.log("compiling");

    await task('clean', null, data);
    await task('configure', null, data);
    await task('build', filterErrors, data);

    return 0;
}

async function task(value, filter, data) {
    const task = await proc(value, filter);
    // let task = taskComplete(configure.success, value, configure.output);
    if (data(taskComplete(task.success, value, task.output)))
        return -1;
    else
        return 0;
}

function proc(action, filterOutput) {
    return new Promise((resolve, reject) => {
        const output = [];
        const proc = exec(`node-gyp ${action}`);
        proc.stdout.on('data', data => output.push(data));

        proc.on('exit', status => {
            const errors = typeof filterOutput === "function" ? filterOutput(output) : output;
            resolve({ success: status, output: errors });
        });
    });
}

function taskComplete(code, action, output) {
    if (code !== 0)
        return `\u001b[33m${action} - Fail (${code}) \u001b[0m\u001b[31m\n${output}\u001b[0m`;
    else
        return `\u001b[34m${action} - success (${code}) \u001b[0m`;
}