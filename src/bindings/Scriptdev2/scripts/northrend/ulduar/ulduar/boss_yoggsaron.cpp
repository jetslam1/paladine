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
SDName: Yogg-Saron
SD%Complete: 0
SDComment: PH.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"


#define SOUND_UR_YoggSaron_PhaseTwo01   15754
#define SOUND_UR_YoggSaron_PhaseThree01 15755
#define SOUND_UR_YoggSaron_Tentacle01   15756
#define SOUND_UR_YoggSaron_Slay01       15757
#define SOUND_UR_YoggSaron_Slay02       15758
#define SOUND_UR_YoggSaron_Insanity01   15759
#define SOUND_UR_YoggSaron_Insanity02   15760
#define SOUND_UR_YoggSaron_Death01      15761
#define SOUND_UR_YoggSaron_YSVisOne01   15762
#define SOUND_UR_YoggSaron_YSVisOne02   15763
#define SOUND_UR_YoggSaron_YSVisOne03   15764
#define SOUND_UR_YoggSaron_YSVisTwo03   15765
#define SOUND_UR_YoggSaron_YSVisThree01 15766
#define SOUND_UR_YoggSaron_YSVisThree02 15767
#define SOUND_UR_YoggSaron_Wound        15768
#define SOUND_UR_YoggSaron_WoundCrit    15769
#define SOUND_UR_YoggSaron_Attack       15770
#define SOUND_UR_FemaleYogg_Prefight01  15771
#define SOUND_UR_FemaleYogg_Prefight02  15772
#define SOUND_UR_FemaleYogg_Help01      15773
#define SOUND_UR_FemaleYogg_Help02      15774
#define SOUND_UR_FemaleYogg_Aggro01     15775
#define SOUND_UR_FemaleYogg_Special01   15776
#define SOUND_UR_FemaleYogg_Special02   15777
#define SOUND_UR_FemaleYogg_Slay01      15778
#define SOUND_UR_FemaleYogg_Slay02      15779
#define SOUND_UR_FemaleYogg_Insanity01  15780
#define SOUND_UR_FemaleYogg_Wound       15781
#define SOUND_UR_FemaleYogg_WoundCrit   15782
#define SOUND_UR_FemaleYogg_Attack      15783

// Sara - Phase 1
#define SPELL_SARAS_FERVOR              63138
#define SPELL_SARAS_BLESSING            63134
#define SPELL_SARAS_ANGER               63147

// Sara - Phase 2
#define SPELL_DEATH_RAY                 63891
#define SPELL_SHADOWY_BARRIER           64775 
#define SPELL_BRAIN_LINK                63802
#define SPELL_MALADY_OF_THE_MIND        63830
#define SPELL_PSYCHOSIS                 63795

// Yogg-Sarons Gehirn
#define SPELL_INDUCE_MADNESS            64059
#define SPELL_SHATTERED_ILLUSION        64173

// Yogg-Saron Phase 2
#define AURA_SHADOWY_BARRIER_1          63894

// Yogg-Saron Phase 3
#define SPELL_EMPOWERING_SHADOWS        64486
#define SPELL_SHADOW_BEACON             64465
#define SPELL_LUNATIC_GAZE              64164
#define SPELL_EXINGUISH_ALL_LIFE        64166

// Freya - Freundlicher Wächter
#define SPELL_SANITY_WELL               64170
#define AURA_RESILIENCE_OF_NATURE       62670

// Hodir - Freundlicher Wächter
#define AURA_FORTITUDE_OF_FROST         62650
#define SPELL_HODIRS_PROTECTIVE_GAZE    64174

// Mimiron - Freundlicher Wächter
#define AURA_SPEED_OF_INVENTION         62671
#define SPELL_DESTABILIZATION_MATRIX    65210

// Thorim - Freundlicher Wächter
#define AURA_FURY_OF_THE_STORM          62702
#define SPELL_TITANIC_STORM             64172

// Ominöse Wolke - Phase 1
#define AURA_SUMMON_GUARDIAN            62979

// Sanity Well
#define AURA_SANITY_WELL                63288

// Wächter von Yogg-Saron - Phase 1
#define SPELL_DOMINATE_MIND             63042
#define SPELL_SHADOW_NOVA               62714
#define SPELL_DARK_VOLLEY               63038

// Schmettertentakel - Phase 2
#define SPELL_ERUPT                     64144
#define SPELL_DIMINISH_POWER            64145
#define SPELL_FOCUSED_ANGER             57688
#define SPELL_CRUSH                     64147



struct MANGOS_DLL_DECL boss_yoggsaronAI : public Scripted_NoMovementAI
{
    boss_yoggsaronAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_SHADOWY_BARRIER_1, 0))
            m_creature->CastSpell(m_creature, AURA_SHADOWY_BARRIER_1, true);

		if(!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    void Aggro(Unit* pWho)
    {
		DoPlaySoundToSet(m_creature, SOUND_UR_FemaleYogg_Aggro01);
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

// Freya - Freundlicher Wächter
struct MANGOS_DLL_DECL npc_freya_helpAI : public ScriptedAI
{
    npc_freya_helpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_RESILIENCE_OF_NATURE, 0))
            m_creature->CastSpell(m_creature, AURA_RESILIENCE_OF_NATURE, true);
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
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

// Thorim - Freundlicher Wächter
struct MANGOS_DLL_DECL npc_thorim_helpAI : public ScriptedAI
{
    npc_thorim_helpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_FURY_OF_THE_STORM, 0))
            m_creature->CastSpell(m_creature, AURA_FURY_OF_THE_STORM, true);
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
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};


// Hodir - Freundlicher Wächter
struct MANGOS_DLL_DECL npc_hodir_helpAI : public ScriptedAI
{
    npc_hodir_helpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_FORTITUDE_OF_FROST, 0))
            m_creature->CastSpell(m_creature, AURA_FORTITUDE_OF_FROST, true);
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
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

// Mimiron - Freundlicher Wächter
struct MANGOS_DLL_DECL npc_mimiron_helpAI : public ScriptedAI
{
    npc_mimiron_helpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_SPEED_OF_INVENTION , 0))
            m_creature->CastSpell(m_creature, AURA_SPEED_OF_INVENTION , true);
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
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};


// Sanity Well
struct MANGOS_DLL_DECL npc_sanity_wellAI : public ScriptedAI
{
    npc_sanity_wellAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
	    if(!m_creature->HasAura(AURA_SANITY_WELL  , 0))
            m_creature->CastSpell(m_creature, AURA_SANITY_WELL  , true);
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
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

// Sara - Phase 1
struct MANGOS_DLL_DECL npc_saraAI : public Scripted_NoMovementAI
{
    npc_saraAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;

	bool Phase2;

    void Reset()
    {
        Phase2 = false;

		if(!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
		    Phase2 = true;
			DoCast(m_creature, SPELL_SHADOWY_BARRIER);
			m_creature->SummonCreature(NPC_YOGGSARON, 1976.812f, -25.675f, 330.980f, 3.124, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

            DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

CreatureAI* GetAI_npc_sara(Creature *_Creature)
{
    return new npc_saraAI(_Creature);
}

CreatureAI* GetAI_npc_sanity_well(Creature* pCreature)
{
    return new npc_sanity_wellAI(pCreature);
}

CreatureAI* GetAI_npc_mimiron_help(Creature* pCreature)
{
    return new npc_mimiron_helpAI(pCreature);
}

CreatureAI* GetAI_npc_hodir_help(Creature* pCreature)
{
    return new npc_hodir_helpAI(pCreature);
}

CreatureAI* GetAI_npc_thorim_help(Creature* pCreature)
{
    return new npc_thorim_helpAI(pCreature);
}

CreatureAI* GetAI_npc_freya_help(Creature* pCreature)
{
    return new npc_freya_helpAI(pCreature);
}

CreatureAI* GetAI_boss_yoggsaron(Creature *_Creature)
{
    return new boss_yoggsaronAI(_Creature);
}

void AddSC_boss_yoggsaron()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_yoggsaron";
    newscript->GetAI = &GetAI_boss_yoggsaron;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_freya_help";
    newscript->GetAI = &GetAI_npc_freya_help;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_thorim_help";
    newscript->GetAI = &GetAI_npc_thorim_help;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_hodir_help";
    newscript->GetAI = &GetAI_npc_hodir_help;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_mimiron_help";
    newscript->GetAI = &GetAI_npc_mimiron_help;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_sanity_well";
    newscript->GetAI = &GetAI_npc_sanity_well;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_sara";
    newscript->GetAI = &GetAI_npc_sara;
    newscript->RegisterSelf();

}

