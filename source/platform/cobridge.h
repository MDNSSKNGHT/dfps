/*
 * Copyright (C) 2021-2022 Matt Yang
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "singleton.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class CoBridge : public Singleton<CoBridge> {
public:
    using SubscribeCallback = std::function<void(const void *)>;

    CoBridge();
    void Publish(const std::string &theme, const void *data) const;
    void Subscribe(const std::string &theme, const SubscribeCallback &cb);
    bool HasSubscriber(const std::string &theme) const;

    template <typename T>
    static const T &Get(const void *data) {
        return *reinterpret_cast<const T *>(data);
    }

private:
    std::unordered_map<std::string, std::vector<SubscribeCallback>> pubsub_;
};