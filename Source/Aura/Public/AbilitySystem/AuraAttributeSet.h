#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    FEffectProperties()
    {
    }

    FGameplayEffectContextHandle EffectContextHandle;

    UPROPERTY()
    UAbilitySystemComponent* SourceASC = nullptr;

    UPROPERTY()
    AActor* SourceAvatarActor = nullptr;

    UPROPERTY()
    AController* SourceController = nullptr;

    UPROPERTY()
    ACharacter* SourceCharacter = nullptr;

    UPROPERTY()
    UAbilitySystemComponent* TargetASC = nullptr;

    UPROPERTY()
    AActor* TargetAvatarActor = nullptr;

    UPROPERTY()
    AController* TargetController = nullptr;

    UPROPERTY()
    ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the  FGameplayAttribute() signature, but TStaticFuncPtr is generic to any signature chosen
template <typename Type>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<Type, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UAuraAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

    /*
     * Secondary Attributes
     */

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Armor", Category = "Attributes|Secondary")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_ArmorPenetration", Category = "Attributes|Secondary")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_BlockChance", Category = "Attributes|Secondary")
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_CriticalHitChance", Category = "Attributes|Secondary")
    FGameplayAttributeData CriticalHitChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_CriticalHitDamage", Category = "Attributes|Secondary")
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_CriticalHitResistance", Category = "Attributes|Secondary")
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_HealthRegeneration", Category = "Attributes|Secondary")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_ManaRegeneration", Category = "Attributes|Secondary")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Health", Category = "Attributes|Secondary")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxHealth", Category = "Attributes|Secondary")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

    /*
     * Primary Attributes
     */

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Strength", Category = "Attributes|Primary")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Intelligence", Category = "Attributes|Primary")
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Resilience", Category = "Attributes|Primary")
    FGameplayAttributeData Resilience;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Vigor", Category = "Attributes|Primary")
    FGameplayAttributeData Vigor;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

    /*
     * Vital Attributes
     */

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Mana", Category = "Attributes|Vital")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_MaxMana", Category = "Attributes|Vital")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

    /*
     * Meta Attributes
     */

    UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
    FGameplayAttributeData IncomingDamage;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

    UFUNCTION()
    void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

    UFUNCTION()
    void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

    UFUNCTION()
    void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

    UFUNCTION()
    void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

    UFUNCTION()
    void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

private:
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
    void ShowFloatingText(const FEffectProperties& Props, const float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
