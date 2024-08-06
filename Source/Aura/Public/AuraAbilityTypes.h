#pragma once
#include "GameplayEffectTypes.h"

#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

public:
    bool IsCriticalHit() const { return bIsCriticalHit; }
    bool IsBlockedHit() const { return bIsBlockedHit; }

    void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
    void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }

    /** Returns the actual struct used for serialization, subclasses must override this! */
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return GetScriptStruct();
    }

    /** Creates a copy of this context, used to duplicate for later modifications */
    virtual FAuraGameplayEffectContext* Duplicate() const
    {
        FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
        *NewContext = *this;
        if (GetHitResult())
        {
            // Does a deep copy of the hit result
            NewContext->AddHitResult(*GetHitResult(), true);
        }
        return NewContext;
    }

    /** Custom serialization, subclasses must override this */
    virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
    UPROPERTY()
    bool bIsBlockedHit = false;

    UPROPERTY()
    bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,           // struct has a NetSerialize function for serializing its state to an FArchive used for network replication.
        WithCopy = true                     // struct can be copied via its copy assignment operator.
    };
};
