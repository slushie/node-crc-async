{
  "targets": [
    {
      "target_name": "crcp",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "include"
      ],
      "sources": [
        "lib/7zCrc.c",
        "lib/7zCrcOpt.c",
        "lib/CpuArch.c",
        "src/module.cc"
      ]
    }
  ]
}
