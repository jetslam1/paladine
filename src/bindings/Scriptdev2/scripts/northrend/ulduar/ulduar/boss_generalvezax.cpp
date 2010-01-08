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
#define SPELL_AURA_OF_DESPAIR      62692
#define SPELL_MARK_OF_THE_FACELESS 63276
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
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();

        Reset();
    }

    ScriptedInstance* m_pInstance;
	bool m_bIsRegularMode;

	uint32 Searing_Flames_Timer;
	uint32 Shadow_Crash_Timer;
	uint32 Mark_of_the_Faceless_Timer;
	uint32 Surge_of_Darkness_Timer;
	uint32 Saronite_Barrier_Timer;
	uint32 Berserk_Timer;
	bool berserk;

    void Reset()
    {
		Searing_Flames_Timer = 10000;
		Shadow_Crash_Timer = 15000;
		Mark_of_the_Faceless_Timer = 40000;
		Surge_of_Darkness_Timer = 30000;
		Saronite_Barrier_Timer = 35000;
		Berserk_Timer = 900000;
		if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, NOT_STARTED);
    }

    void KilledUnit(Unit *victim)
    {
		switch(urand(0, 1))
                {
                    case 0: 
						DoPlaySoundToSet(m_creature, SOUND_UR_Vezax_Slay01); 
						break;
                    case 1:
						DoPlaySoundToSet(m_creature, SOUND_UR_Vezax_Slay02);
						break;
                }
    }

    void JustDied(Unit *victim)
    {
		if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, DONE);
		DoPlaySoundToSet(m_creature, SOUND_UR_Vezax_Death01);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, IN_PROGRESS);
		DoPlaySoundToSet(m_creature, SOUND_UR_Vezax_Aggro01);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Searing_Flames_Timer < diff )
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(m_creature->getVictim(), SPELL_SEARING_FLAMES);
            Searing_Flames_Timer = 25000;
        }else Searing_Flames_Timer -= diff;

		if (Shadow_Crash_Timer < diff )
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(m_creature->getVictim(), SPELL_SHADOW_CRASH);
            Shadow_Crash_Timer = 15000;
        }else Shadow_Crash_Timer -= diff;

		if (Mark_of_the_Faceless_Timer < diff )
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(m_creature->getVictim(), SPELL_MARK_OF_THE_FACELESS);
            Mark_of_the_Faceless_Timer = 40000;
        }else Mark_of_the_Faceless_Timer -= diff;

		if (Berserk_Timer < diff && !berserk)
        {
            m_creature->CastStop();
            DoCast(m_creature, SPELL_BERSERK);
            berserk = true;
        }else Berserk_Timer -= diff;

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
