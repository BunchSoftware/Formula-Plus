import QtQuick 2.0
import QtQuick.Layouts 1.14

Item {
    id: root
    QtObject {
        id: internals
        property string markdown_text: "
# Formula Plus Docs RU
Пользовательская документация Formula Plus на русском

## Оглавление
1. [Введение](getting-started.md)
2. [Объяснение физики и физических формул](base-physic.md)
3. [Математический парсер](math-parser.md)
4. [Физический парсер](physic-parser.md)
5. [Путь развития приложения](roadmap.md)
6. [Ручное тестирование Formula Plus](physical-calculator-manual-tests.md)
6. [Поддержка](support.md)
7. [Жизнь проект](health-project.md)

## Описание коммитов
| Название | Описание                                                        |
|----------|-----------------------------------------------------------------|
| build	   | Сборка проекта или изменения внешних зависимостей               |
| sec      | Безопасность, уязвимости                                        |
| docs	   | Обновление документации                                         |
| feat	   | Добавление нового функционала                                   |
| fix	   | Исправление ошибок                                              |
| perf	   | Изменения направленные на улучшение производительности          |
| refactor | Правки кода без исправления ошибок или добавления новых функций |
| revert   | Откат на предыдущие коммиты                                     |
"
    }

    RowLayout {
        anchors.fill: parent
        Text {
            id: t_output
            Layout.fillWidth: true
            textFormat: TextEdit.MarkdownText
            text: internals.markdown_text
        }
    }
}
