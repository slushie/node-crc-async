{
  "targets": [
    {
      "target_name": "crc-async",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "include"
      ],
      "sources": [
        "lib/7zCrc.c",
        "lib/7zCrcOpt.c",
        "lib/CpuArch.c",
        "src/module.cc",
        "src/crc.cc",
        "src/async-crc.cc"
      ]
    }
  ]
}
