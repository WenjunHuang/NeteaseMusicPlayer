//
// Created by HUANG WEN JUN on 2019/11/28.
//
#pragma once
#include "executor.h"
#include "json.h"
#include "logger.h"
#include "misc.h"
#include "magic_enum.hpp"
#include "sqlite_orm.h"

template<typename ... Ts>
struct overload : Ts ... {
    using Ts::operator() ...;
};

template<typename...Ts>
overload(Ts...) -> overload<Ts...>;
