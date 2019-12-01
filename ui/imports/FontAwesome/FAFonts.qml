pragma Singleton
import QtQuick 2.12

QtObject {
id: fonts
readonly property FontLoader fontAwesomeRegular: FontLoader {
    source: "./fa-regular-400.ttf"
}
readonly property FontLoader fontAwesomeLight: FontLoader {
    source: "./fa-light-300.ttf"
}
readonly property FontLoader fontAwesomeSolid: FontLoader {
    source: "./fa-solid-900.ttf"
}

readonly property FontLoader fontAwesomeBrands: FontLoader{
source:"./fa-brands-400.ttf"
}
readonly property FontLoader fontAwesomeDuotone: FontLoader{
source:"./fa-duotone-900.ttf"
}

readonly property string regular: fontAwesomeRegular.name
readonly property string light: fontAwesomeLight.name
readonly property string solid: fontAwesomeSolid.name
readonly property string brands : fontAwesomeBrands.name
readonly property string duotone : fontAwesomeDuotone.name

}