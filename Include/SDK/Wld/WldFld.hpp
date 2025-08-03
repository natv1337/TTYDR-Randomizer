#pragma once

#include "Util.hpp"
#include "WldHandle.hpp"

namespace wld {
namespace fld {

class State {
public:
    virtual ~State();

private:
    char m_name[64];
    s32 m_stateManagerIndex;
    s32 int4C;
    bool bool50;
    class Manager* m_fldManager;
    s32 int60;
};
ASSERT_SIZE(State, 0x68);

class StateManager {
public:
    virtual ~StateManager();

private:
    State** m_states;
    char pad_0010[0x10];
    State* m_currentState;
    bool m_initialized;

};
ASSERT_SIZE(StateManager, 0x30);

namespace col {

class Manager {
public:
    virtual ~Manager();

private:
    char pad_0008[0x20];
};
ASSERT_SIZE(Manager, 0x28);

}

namespace data {

struct ItemData;

struct Parameter {
    char* Identifier;
    float FloatValue;
    char* StringValue;
};
ASSERT_SIZE(Parameter, 0x18);

} // namespace wld::fld::data

namespace mobj {

class Manager;

class Mobj {
};

class MobjHandle : public wld::Handle<Mobj> {};

};

namespace npc {

class Manager;

} // namespace wld::fld::npc

namespace party {

class Manager;

} // namespace wld::fld::party

namespace player {

class Manager;

} // namespace wld::fld::player

class Manager {
public:
    virtual ~Manager();

    GET_STATIC_INSTANCE(Manager, 0x2546900)

private:
    bool m_managersInitialized;
    StateManager* m_stateManager;
    player::Manager* m_playerManager;
    npc::Manager* m_npcManager;
    party::Manager* m_partyManager;
    mobj::Manager* m_mobjManager;
};

data::ItemData* getItemDataArray();

data::Parameter* getParameter(const char* param, s32 offset = 0);
float getFloatParameter(const char* param, s32 offset = 0);
char* getStringParameter(const char* param, s32 offset = 0);

} // namespace wld::fld

} // namespace wld