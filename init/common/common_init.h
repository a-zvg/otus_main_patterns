#pragma once

#include "common/i_object.h"
#include <vector>

/// @brief Обобщенный алгоритм создания и инициализации объектов
/// @param initList Массив названий команд инициализации
/// @param count Количество создаваемых объектов
/// @return Массив созданных и проинициализированных объектов
std::vector<IObjectSP> CommonInit( const std::vector<std::string>& initList, size_t count );
