#include <macro_command/common/u_object.h>
#include <macro_command/common/macro_command.h>

#include <macro_command/move/move_command.h>
#include <macro_command/move/movable_adapter.h>

#include <macro_command/fuel/check_fuel_command.h>
#include <macro_command/fuel/fuel_checkable_adapter.h>
#include <macro_command/fuel/burn_fuel_command.h>
#include <macro_command/fuel/fuel_burnable_adapter.h>

#include <gmock/gmock.h>
#include <exception>
#include <memory>
#include <iostream>

IObjectSP MakeTankWithFuel( Point position, Point velocity, int fuelLevel, int fuelBurnSpeed )
{
    IObjectSP uObj = std::make_shared<UObject>();
    uObj->Set( "Position", position );
    uObj->Set( "Velocity", velocity );
    uObj->Set( "FuelLevel", fuelLevel );
    uObj->Set( "FuelBurnSpeed", fuelBurnSpeed );

    return uObj;
}

TEST( MoveCommandWithBurnFuel, Test )
{
    Point position = { 0, 0 };
    int fuelLevel = 100;
    IObjectSP uObj = MakeTankWithFuel( position, Point{ 1, 1 }, fuelLevel, 10 );

    auto moveCmd = std::make_unique<MoveCommand>( std::make_unique<MovableAdapter>( uObj ) );
    auto checkFuelCmd = std::make_unique<CheckFuelCommand>( std::make_unique<FuelCheckableAdapter>( uObj ) );
    auto burnFuelCmd = std::make_unique<BurnFuelCommand>( std::make_unique<FuelBurnableAdapter>( uObj ) );

    MacroCommand moveCommandWithBurnFuel( std::move( checkFuelCmd ) );
    EXPECT_NO_THROW( moveCommandWithBurnFuel.Add( std::move( moveCmd ) ) );
    EXPECT_NO_THROW( moveCommandWithBurnFuel.Add( std::move( burnFuelCmd ) ) );

    auto moveAdapter = std::make_unique<MovableAdapter>( uObj );
    auto checkFuelAdapter = std::make_unique<FuelCheckableAdapter>( uObj );
    for ( int i = 1; i <= 10; ++i )
    {
        EXPECT_NO_THROW( moveCommandWithBurnFuel.Execute() );
        EXPECT_EQ( checkFuelAdapter->GetFuelLevel(), fuelLevel - i*10 );
        EXPECT_EQ( moveAdapter->GetPosition(), ( position + Point{ i, i } ) );
    }

    EXPECT_THROW( moveCommandWithBurnFuel.Execute(), CommandError );
    EXPECT_EQ( checkFuelAdapter->GetFuelLevel(), 0 );
    EXPECT_EQ( moveAdapter->GetPosition(), ( Point{ 10, 10 } ) );
}
