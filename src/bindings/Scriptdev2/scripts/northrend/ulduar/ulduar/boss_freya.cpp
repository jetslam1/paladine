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

/*
#define SAY_AGGRO -1
#define SAY_SLAY -1
*/

#define GOSSIP_START_FREYA_EVENT     "Im ready for The Descent into Madness."

#define NPC_FREYA_DEATH    33241
#define NPC_FREYA_HELP     33410
#define NPC_SANITY_WELL    33991

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
		m_creature->SummonCreature(NPC_FREYA_DEATH, 1944.715f, 34.830f, 411.357f, 5.283, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000000);
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

struct MANGOS_DLL_DECL npc_freya_deathAI : public ScriptedAI
{
    npc_freya_deathAI(Creature* pCreature) : ScriptedAI(pCreature)
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
		m_creature->SummonCreature(NPC_FREYA_HELP, 1939.287f, 42.167f, 338.459f, 4.864, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000000);
		m_creature->SummonCreature(NPC_SANITY_WELL, 1894.562f, 1.227f, 332.699f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000000);
		m_creature->SummonCreature(NPC_SANITY_WELL, 1893.026f, -50.150f, 332.890f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000000);
		m_creature->SummonCreature(NPC_SANITY_WELL, 1992.024f, -91.553f, 330.021f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000000);
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

CreatureAI* GetAI_npc_freya_death(Creature* pCreature)
{
    return new npc_freya_deathAI(pCreature);
}

bool GossipHello_npc_freya_death(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_FREYA_EVENT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_freya_death(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((npc_freya_deathAI*)pCreature->AI())->StartEvent(pPlayer);
    }

    return true;
}

CreatureAI* GetAInpc_freya_death(Creature* pCreature)
{
    return new npc_freya_deathAI(pCreature);
}

CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}

void AddSC_boss_freya()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &GetAI_boss_freya;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_freya_death";
    newscript->GetAI = &GetAI_npc_freya_death;
    newscript->pGossipHello = &GossipHello_npc_freya_death;
    newscript->pGossipSelect = &GossipSelect_npc_freya_death;
    newscript->RegisterSelf();

}

