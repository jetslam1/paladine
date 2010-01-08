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
SDName: General Vezax
SD%Complete: 10%
SDComment: PH.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

// General Vezax Spells
#define SPELL_BERSERK              26662
#define SPELL_AURA_OF DESPAIR      62692
#define SPELL_MARK_OF_THE FACELESS 63276
#define SPELL_SARONITE_BARRIER     63364
#define SPELL_SEARING_FLAMES       62661
#define SPELL_SHADOW_CRASH         62660
#define SPELL_SURGE_OF_DARKNESS    62662

// General Vezax Sounds
#define SOUND_UR_Vezax_Aggro01     15542
#define SOUND_UR_Vezax_Attack      15550
#define SOUND_UR_Vezax_Berserk01   15547
#define SOUND_UR_Vezax_Death01     15546
#define SOUND_UR_Vezax_HardMode01  15548
#define SOUND_UR_Vezax_Kite01      15545
#define SOUND_UR_Vezax_Slay01      15543
#define SOUND_UR_Vezax_Slay02      15544
#define SOUND_UR_Vezax_Wound       15549
#define SOUND_UR_Vezax_WoundCrit   15551

// General Vezax Says
/*
#define SAY_AGGRO -1
#define SAY_SLAY -1
*/

struct MANGOS_DLL_DECL boss_generalvezaxAI : public ScriptedAI
{
    boss_generalvezaxAI(Creature* pCreature) : ScriptedAI(pCreature)
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
        DoScriptText(SOUND_UR_Vezax_Aggro01, m_creature);
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, IN_PROGRESS);
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

CreatureAI* GetAI_boss_generalvezax(Creature* pCreature)
{
    return new boss_generalvezaxAI(pCreature);
}

void AddSC_boss_vezax()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_generalvezax";
    newscript->GetAI = &GetAI_boss_generalvezax;
    newscript->RegisterSelf();

}
/*UPDATE `creature_template` SET `ScriptName`='boss_generalvezax' WHERE (`entry`='33271') LIMIT 1*/
