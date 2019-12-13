"""
Convert FontAwesome's `icons.json` to QML.

This script creates a QML component which defines
constants for all FontAwesome icons listed in the file
`icons.json` in the FontAwesome package.
"""

import sys
import io


def _dash2cap(name):
    try:
        while True:
            idx = name.index("-")
            pre = name[0:idx]
            suf = name[idx + 2:]
            cap = name[idx + 1:idx + 2].capitalize()
            name = pre + cap + suf
    except ValueError:
        pass
    return name


def _main(argv):
    import json
    if len(argv) != 3:
        print("Usage:")
        msg = "    {} path/to/icons.json path/to/Icons.qml"
        msg = msg.format(argv[0])
        print(msg)
        sys.exit(1)
    with io.open(argv[1], "r", encoding="utf-8-sig") as file:
        icons = json.load(file)
    lines = []
    lines.append("pragma Singleton")
    lines.append("import QtQuick 2.13")
    #lines.append('import "./FAFonts.qml"')
    lines.append("")
    lines.append("QtObject {")
    for key, value in icons.items():
        for style in value["styles"]:
            name = "fa-" + key + "-" + style
            name = _dash2cap(name)
            code = "\\u" + value["unicode"]
            if style == "brands":
                weight = "Font.Normal"
            if style == "duotone":
                weight = "Font.Bold"
            if style == "light":
                weight = "Font.Light"
            if style == "regular":
                weight = "Font.Normal"
            if style == "solid":
                weight = "Font.Bold"
            lines.append(f"""    readonly property var {name}: QtObject{{
                        property var family:FAFonts.{style}
                        property var weight: {weight}
                        property string code: "{code}"
                        }}""")
    lines.append("}")
    with open(argv[2], "w") as file:
        file.write("\n".join(lines))


if __name__ == '__main__':
    _main(sys.argv)
