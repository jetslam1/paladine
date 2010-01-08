/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Freya
SD%Complete: 0
SDComment: PH.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

#define GOSSIP_START     "Port to The Descent into Madness ?"

/*
#define SAY_AGGRO -1
#define SAY_SLAY -1
*/

struct MANGOS_DLL_DECL boss_freyaAI : public ScriptedAI
{
    boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    void Aggro(Unit* pWho)
    {
//        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
//SPELLS TODO:

//
        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}

struct MANGOS_DLL_DECL boss_freya_helpAI : public ScriptedAI
{
    boss_freya_helpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    void Aggro(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

CreatureAI* GetAI_boss_freya_help(Creature* pCreature)
{
    return new boss_freya_helpAI(pCreature);
}

struct MANGOS_DLL_DECL boss_freya_copyAI : public ScriptedAI
{
    boss_freya_copyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

    void BeginFreyaCopyEvent(Player* pPlayer)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        DoMeleeAttackIfReady();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim()) return;

        if (!m_pInstance)
            return;
    }
};

CreatureAI* GetAI_boss_freya_copy(Creature* pCreature)
{
    return new boss_freya_copyAI(pCreature);
}

bool GossipHello_boss_freya_copy(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_boss_freya_copy(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((boss_freya_copyAI*)pCreature->AI())->BeginFreyaCopyEvent(pPlayer);
    }

    return true;
}

void AddSC_boss_freya()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_freya";
    NewScript->GetAI = &GetAI_boss_freya;
    NewScript->RegisterSelf();

	NewScript = new Script;
    NewScript->Name = "boss_freya_help";
    NewScript->GetAI = &GetAI_boss_freya_help;
    NewScript->RegisterSelf();

	NewScript = new Script;
    NewScript->Name = "boss_freya_copy";
    NewScript->GetAI = &GetAI_boss_freya_copy;
    NewScript->pGossipHello = &GossipHello_boss_freya_copy;
    NewScript->pGossipSelect = &GossipSelect_boss_freya_copy;
    NewScript->RegisterSelf();

}

/* UPDATE `creature_template` SET `ScriptName`='boss_freya' WHERE (`entry`='32906');
   UPDATE `creature_template` SET `ScriptName`='boss_freya_copy' WHERE (`entry`='33241');
   UPDATE `creature_template` SET `ScriptName`='boss_freya_help' WHERE (`entry`='33410')
   UPDATE `creature_template` SET `npcflag`='1' WHERE (`entry`='33241'); */

