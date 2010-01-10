/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "BattleGround.h"
#include "BattleGroundRV.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "Player.h"
#include "WorldPacket.h"
#include "GameObject.h"

BattleGroundRV::BattleGroundRV()
{

    m_StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set messageIds
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

BattleGroundRV::~BattleGroundRV()
{

}

void BattleGroundRV::Update(uint32 diff)
{
    BattleGround::Update(diff);
}

void BattleGroundRV::StartingEventCloseDoors()
{
}

void BattleGroundRV::StartingEventOpenDoors()
{
}

void BattleGroundRV::AddPlayer(Player *plr)
{
    BattleGround::AddPlayer(plr);
    //create score and add it to map, default values are set in constructor
    BattleGroundRVScore* sc = new BattleGroundRVScore;

    m_PlayerScores[plr->GetGUID()] = sc;

    UpdateArenaWorldState();
}

void BattleGroundRV::RemovePlayer(Player * /*plr*/, uint64 /*guid*/)
{
    if (GetStatus() == STATUS_WAIT_LEAVE)
        return;

    UpdateArenaWorldState();
    CheckArenaWinConditions();
}

void BattleGroundRV::HandleKillPlayer(Player* player, Player* killer)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    if (!killer)
    {
        sLog.outError("BattleGroundRV: Killer player not found");
        return;
    }

    BattleGround::HandleKillPlayer(player, killer);

    UpdateArenaWorldState();
    CheckArenaWinConditions();
}

bool BattleGroundRV::HandlePlayerUnderMap(Player *player)
{
    player->TeleportTo(GetMapId(), 763.5, -284, 28.276, 2.422, false);
    return true;
}

void BattleGroundRV::HandleAreaTrigger(Player *Source, uint32 Trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    switch(Trigger)
    {
        case 5224:
        case 5226:
            break;
        default:
            sLog.outError("WARNING: Unhandled AreaTrigger in Battleground: %u", Trigger);
            Source->GetSession()->SendAreaTriggerMessage("Warning: Unhandled AreaTrigger in Battleground: %u", Trigger);
            break;
    }
}

void BattleGroundRV::FillInitialWorldStates(WorldPacket &data)
{
    data << uint32(0xe1a) << uint32(1);
    UpdateArenaWorldState();
}

void BattleGroundRV::Reset()
{
    //call parent's class reset
    BattleGround::Reset();
}

bool BattleGroundRV::SetupBattleGround()
{
    return true;
}
