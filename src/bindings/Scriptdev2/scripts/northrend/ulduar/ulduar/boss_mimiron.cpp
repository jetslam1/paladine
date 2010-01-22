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
SDName: Mimiron
SD%Complete: 0
SDComment: PH.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

/*
#define SAY_AGGRO -1
#define SAY_SLAY -1
*/

#define GOSSIP_START_MIMIRON_EVENT     "Im ready for The Descent into Madness."

#define NPC_MIMIRON_DEATH    33244
#define NPC_MIMIRON_HELP     33412

struct MANGOS_DLL_DECL boss_mimironAI : public ScriptedAI
{
    boss_mimironAI(Creature* pCreature) : ScriptedAI(pCreature)
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
		m_creature->SummonCreature(NPC_MIMIRON_DEATH, 2030.199f, 18.773, 411.359f, 3.918, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_MIMIRON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

struct MANGOS_DLL_DECL npc_mimiron_deathAI : public ScriptedAI
{
    npc_mimiron_deathAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

	void StartEvent(Player* pPlayer)
    {
		m_creature->SummonCreature(NPC_MIMIRON_HELP, 2036.237f, 25.852f, 338.415f, 3.888, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000000);
		m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
		m_creature->SetVisibility(VISIBILITY_OFF);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

CreatureAI* GetAI_npc_mimiron_death(Creature* pCreature)
{
    return new npc_mimiron_deathAI(pCreature);
}

bool GossipHello_npc_mimiron_death(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_MIMIRON_EVENT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_mimiron_death(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((npc_mimiron_deathAI*)pCreature->AI())->StartEvent(pPlayer);
    }

    return true;
}

CreatureAI* GetAInpc_mimiron_death(Creature* pCreature)
{
    return new npc_mimiron_deathAI(pCreature);
}

CreatureAI* GetAI_boss_mimiron(Creature* pCreature)
{
    return new boss_mimironAI(pCreature);
}

void AddSC_boss_mimiron()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_mimiron";
    newscript->GetAI = &GetAI_boss_mimiron;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_mimiron_death";
    newscript->GetAI = &GetAI_npc_mimiron_death;
    newscript->pGossipHello = &GossipHello_npc_mimiron_death;
    newscript->pGossipSelect = &GossipSelect_npc_mimiron_death;
    newscript->RegisterSelf();

}

