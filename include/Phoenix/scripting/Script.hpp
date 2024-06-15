#pragma once
#include "lua/lua.hpp"
#include <memory>
#include <string>
namespace phnx {
    class Script {
        public:
            static std::shared_ptr<Script> LoadFile(const std::string& filepath);
            Script(lua_State* state);
        
        public:
            void SetupLibs();
            bool PushFunc(const std::string& func);
            void PushInt(int value);
            void PushBool(bool value);
            void PushFloat(float value);
            void PushString(const std::string& str);
            bool TryCall(int argc = 0, int retc = 0);
            void CleanStack(int count = 0);

            bool SimpleCall(const std::string& func);

            bool PushTable(const std::string& func);
            
            template<typename T>
            T GetField(const std::string& field);

        protected:
        private:
            lua_State* L;
    };

    class SpriteScript {
        public:
            SpriteScript(const std::string& filepath);
        public:
            void Init();
            void Render();
            void Update();
        private:
            std::shared_ptr<Script> mScript;
    };
}