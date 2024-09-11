#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
    static const FAuraGameplayTags& Get() { return GameplayTags; }
    static void InitializeNativeGameplayTags();

    // Primary Attributes
    FGameplayTag Attributes_Primary_Strength;
    FGameplayTag Attributes_Primary_Intelligence;
    FGameplayTag Attributes_Primary_Resilience;
    FGameplayTag Attributes_Primary_Vigor;
    // ~Primary Attributes

    // Secondary Attributes
    FGameplayTag Attributes_Secondary_Armor;
    FGameplayTag Attributes_Secondary_ArmorPenetration;
    FGameplayTag Attributes_Secondary_BlockChance;
    FGameplayTag Attributes_Secondary_CriticalHitChance;
    FGameplayTag Attributes_Secondary_CriticalHitDamage;
    FGameplayTag Attributes_Secondary_CriticalHitResistance;
    FGameplayTag Attributes_Secondary_HealthRegeneration;
    FGameplayTag Attributes_Secondary_ManaRegeneration;
    FGameplayTag Attributes_Secondary_MaxHealth;
    FGameplayTag Attributes_Secondary_MaxMana;
    // ~Secondary Attributes

    // Resistances
    FGameplayTag Attributes_Resistances_Fire;
    FGameplayTag Attributes_Resistances_Lightning;
    FGameplayTag Attributes_Resistances_Arcane;
    FGameplayTag Attributes_Resistances_Physical;
    // ~Resistances

    // Input Tags
    FGameplayTag InputTag_LMB;
    FGameplayTag InputTag_RMB;
    FGameplayTag InputTag_1;
    FGameplayTag InputTag_2;
    FGameplayTag InputTag_3;
    FGameplayTag InputTag_4;
    // ~Input Tags

    // Damage Types
    FGameplayTag Damage;
    FGameplayTag Damage_Fire;
    FGameplayTag Damage_Lightning;
    FGameplayTag Damage_Arcane;
    FGameplayTag Damage_Physical;
    // ~Damage Types

    TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

    // Effects
    FGameplayTag Effects_HitReact;
    // ~Effects

protected:

private:
    static FAuraGameplayTags GameplayTags;
};
