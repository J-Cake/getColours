{
  "targets": [
    {
      "target_name": "getWindowsColour",
      "sources": [
        "src/source/entry.cpp",
        "src/source/getColours.cpp"
      ],
      "include_dirs": [
        "src/headers"
      ],
      "libraries": [
        "d2d1.lib"
      ],
      "cflags_cc": ["-std=c++17"]
    }
  ]
}