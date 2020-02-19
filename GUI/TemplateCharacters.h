#pragma once

#include <QString>

class TemplateCharacterInfo {
public:
    TemplateCharacterInfo(const QString& class_name, const QString& setup_string) : class_name(class_name), setup_string(setup_string) {}

    const QString class_name;
    const QString setup_string;
};

class TemplateCharacters {
public:
    static TemplateCharacterInfo template_character_info(const QString& template_char);
};
