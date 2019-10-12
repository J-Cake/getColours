import getColours from './index';

interface colour {
    red: number,
    green: number,
    blue: number,
}

interface colours {
    lightest: colour,
    lighter: colour,
    light: colour,
    accent: colour,
    dark: colour,
    darker: colour,
    darkest: colour
}

export default function (): colours {
    return getColours();
}