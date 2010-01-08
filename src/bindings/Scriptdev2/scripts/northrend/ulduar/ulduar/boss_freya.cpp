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

#define SP_ATTUNED_TO_NATURE 62519 //increases healing, start at 150 stacks
#define SP_TOUCH_OF_EONAR 62528 //heals Freya, 6k per second
#define H_SP_TOUCH_OF_EONAR 62892 //heals Freya, 24k per second
#define SP_SUNBEAM 62623
#define H_SP_SUNBEAM 62872
#define SP_BERSERK 47008
 
 
#define CR_DETONATING_LASHER 32918
#define CR_ANCIENT_CONSERVATOR 33203
#define CR_WATER_SPIRIT 33202
#define CR_STORM_LASHER 32919
#define CR_SNAPLASHER 32916
 
class MANGOS_DLL_DECL AttunedToNatureAura : public Aura
{
    public:
        AttunedToNatureAura(const SpellEntry *spell, uint32 eff, int32 *bp, Unit *target, Unit *caster) : Aura(spell, eff, bp, target, caster, NULL)
            {}
};

struct MANGOS_DLL_DECL boss_freyaAI : public ScriptedAI
{
    boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Regular = pCreature->GetMap()->IsRegularDifficulty();
        sp = (SpellEntry *)GetSpellStore()->LookupEntry(SP_ATTUNED_TO_NATURE);
        bp = 8;
        if(!pCreature->HasAura(SP_ATTUNED_TO_NATURE, 0))
            pCreature->AddAura(new AttunedToNatureAura(sp, 0, &bp, pCreature, pCreature));
        pCreature->GetAura(SP_ATTUNED_TO_NATURE, 0)->SetStackAmount(150);
        Reset();
    }

    uint32 SummonTimer;
    uint32 WaveNumber;
    uint32 WaveType;
    uint32 WaveTypeInc;
    uint32 SunbeamTimer;
    uint32 EnrageTimer;
 
    bool Regular;
    ScriptedInstance *pInstance;
    SpellEntry const *sp;
    int32 bp;

    void Reset()
    {
		SummonTimer = 15000;
        WaveNumber = 0;
        WaveType = irand(0,2);
        WaveTypeInc = irand(1,2);
        SunbeamTimer = rand()%10000;
        EnrageTimer = 600000; //10 minutes
 
        if(!m_creature->HasAura(SP_ATTUNED_TO_NATURE, 0))
            m_creature->AddAura(new AttunedToNatureAura(sp, 0, &bp, m_creature, m_creature));
        m_creature->GetAura(SP_ATTUNED_TO_NATURE, 0)->SetStackAmount(150);
 
        if(pInstance) pInstance->SetData(TYPE_FREYA, NOT_STARTED);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
		if(pInstance) pInstance->SetData(TYPE_FREYA, DONE);
    }

    void Aggro(Unit* pWho)
    {
        if(!m_creature->HasAura(SP_ATTUNED_TO_NATURE, 0))
            m_creature->AddAura(new AttunedToNatureAura(sp, 0, &bp, m_creature, m_creature));
        m_creature->GetAura(SP_ATTUNED_TO_NATURE, 0)->SetStackAmount(150);
 
        DoCast(m_creature, Regular ? SP_TOUCH_OF_EONAR : H_SP_TOUCH_OF_EONAR);
 
        if(pInstance) pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
    }
    void SummonLashers()
    {
        int i;
        float x,y;
        for(i=0; i<10; ++i)
        {
            x = (rand_norm() * 30.0f) - 15.0f;
            y = (rand_norm() * 30.0f) - 15.0f;
            Creature *lasher = DoSpawnCreature(CR_DETONATING_LASHER, x, y, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2000);
            Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0);
            if(lasher && target)
                lasher->AddThreat(target, 1.0f);
        }
    }
 
    void SummonConservator()
    {
        float x = (rand_norm() * 30.0f) - 15.0f;
        float y = (rand_norm() * 30.0f) - 15.0f;
        Creature *add = DoSpawnCreature(CR_ANCIENT_CONSERVATOR, x, y, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2000);
        Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0);
        if(add && target)
            add->AddThreat(target, 1.0f);
    }
 
    void SummonElementals()
    {
        Creature *add;
        Unit *target;
        add = DoSpawnCreature(CR_WATER_SPIRIT, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2000);
        target = SelectUnit(SELECT_TARGET_RANDOM, 0);
        if(add && target)
            add->AddThreat(target, 1.0f);
 
        add = DoSpawnCreature(CR_STORM_LASHER, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2000);
        target = SelectUnit(SELECT_TARGET_RANDOM, 0);
        if(add && target)
            add->AddThreat(target, 1.0f);
 
        add = DoSpawnCreature(CR_SNAPLASHER, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2000);
        target = SelectUnit(SELECT_TARGET_RANDOM, 0);
        if(add && target)
            add->AddThreat(target, 1.0f);
    }
 
    void SummonedCreatureDespawn(Creature* mob)
    {
        if(!m_creature->HasAura(SP_ATTUNED_TO_NATURE, 0)) return;
 
        switch(mob->GetEntry())
        {
            case CR_DETONATING_LASHER:
                if(m_creature->GetAura(SP_ATTUNED_TO_NATURE, 0)->modStackAmount(-2))
                    m_creature->RemoveAurasDueToSpell(SP_ATTUNED_TO_NATURE);
                break;
            case CR_ANCIENT_CONSERVATOR:
                if(m_creature->GetAura(SP_ATTUNED_TO_NATURE, 0)->modStackAmount(-25))
                    m_creature->RemoveAurasDueToSpell(SP_ATTUNED_TO_NATURE);
                break;
            case CR_SNAPLASHER:
            case CR_STORM_LASHER:
            case CR_WATER_SPIRIT:
                if(m_creature->GetAura(SP_ATTUNED_TO_NATURE, 0)->modStackAmount(-10))
                    m_creature->RemoveAurasDueToSpell(SP_ATTUNED_TO_NATURE);
 
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        //Phase 1, waves of adds
        if(WaveNumber < 6)
        {
            if(SummonTimer < diff)
            {
                switch(WaveType)
                {
                    case 0: SummonLashers(); break;
                    case 1: SummonConservator(); break;
                    case 2: SummonElementals(); break;
                }
                WaveType = (WaveType + WaveTypeInc) % 3;
                ++WaveNumber;
                SummonTimer = 60000;
            }
            else SummonTimer -= diff;
        }
            
 
        //All phases
        if(SunbeamTimer < diff)
        {
            if( Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(target, Regular ? SP_SUNBEAM : H_SP_SUNBEAM);
            SunbeamTimer = 6000 + rand()%10000;
        }
        else SunbeamTimer -= diff;
 
        if(EnrageTimer < diff)
        {
            DoCast(m_creature, SP_BERSERK);
            EnrageTimer = 30000;
        }
        else EnrageTimer -= diff;
 
        DoMeleeAttackIfReady();
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

