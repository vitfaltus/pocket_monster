#include "input/ButtonHandler.hpp"

#include <esp32-hal-gpio.h>
#include <HardwareSerial.h>

#include "config.hpp"

ButtonHandler::ButtonHandler(const uint16_t NoPressValue, const uint16_t LeftAnalogValue,
                            const uint16_t MiddleAnalogValue, const uint16_t RightAnalogValue,
                            const uint16_t ShortPressThreshold, const uint16_t LongPressThreshold)
{

    this->NoPressValue = NoPressValue;
    this->LeftAnalogValue = LeftAnalogValue;
    this->MiddleAnalogValue = MiddleAnalogValue;
    this->RightAnalogValue = RightAnalogValue;

    this->ShortPressThreshold = ShortPressThreshold;
    this->LongPressThreshold = LongPressThreshold;

    pinMode(config::PinConfig::BUTTON_PANEL, INPUT);
}

ButtonHandler::ButtonHandler()
{
  this->NoPressValue = config::ButtonInputVals::NoPressValue;
  this->LeftAnalogValue = config::ButtonInputVals::LeftAnalogValue;
  this->MiddleAnalogValue = config::ButtonInputVals::MiddleAnalogValue;
  this->RightAnalogValue = config::ButtonInputVals::RightAnalogValue;

  this->ShortPressThreshold = config::ButtonInputVals::ShortPressThreshold;
  this->LongPressThreshold = config::ButtonInputVals::LongPressThreshold;
}

ButtonHandler::ButtonPress ButtonHandler::checkButtons()
{

    getButtonPanelValue();

    //Serial.println(ButtonPanelValue);

    if (aroundValue(NoPressValue, ButtonPanelValue))
    { // button possibly released
        if (LeftDebounceTimer > ShortPressThreshold)
        {
            return handleLeftRelease();
        }
        if (MiddleDebounceTimer > ShortPressThreshold)
        {
            return handleMiddleRelease();
        }
        if (RightDebounceTimer > ShortPressThreshold)
        {
            return handleRightRelease();
        }
        clearDebounceTimers();
    }
    if (aroundValue(LeftAnalogValue, ButtonPanelValue))
    {

        LeftDebounceTimer++;
    }
    else if (aroundValue(MiddleAnalogValue, ButtonPanelValue))
    {

        MiddleDebounceTimer++;
    }
    else if (aroundValue(RightAnalogValue, ButtonPanelValue))
    {
        RightDebounceTimer++;
    }

    return None;
}

bool ButtonHandler::aroundValue(const uint16_t reference_value, const uint16_t compared_value)
{
    if (std::abs(reference_value - compared_value) < AnalogReadErrorMargin)
    {
        return true;
    }
    return false;
}

ButtonHandler::ButtonPress ButtonHandler::handleLeftRelease()
{

    if (LeftDebounceTimer > LongPressThreshold)
    {
        clearDebounceTimers();
        return LeftButtonLongPress;
    }

    clearDebounceTimers();
    return LeftButtonPress;
}

ButtonHandler::ButtonPress ButtonHandler::handleMiddleRelease()
{
    if (MiddleDebounceTimer > LongPressThreshold)
    {
        clearDebounceTimers();
        return MiddleButtonLongPress;
    }
    clearDebounceTimers();
    return MiddleButtonPress;
}

ButtonHandler::ButtonPress ButtonHandler::handleRightRelease()
{
    if (RightDebounceTimer > LongPressThreshold)
    {
        clearDebounceTimers();
        return RightButtonLongPress;
    }
    clearDebounceTimers();
    return RightButtonPress;
}

void ButtonHandler::getButtonPanelValue()
{
    ButtonPanelValue = 0;

    for (uint16_t i = 0; i < SamplesPerRead; i++)
    {
        ButtonPanelValue += analogRead(config::PinConfig::BUTTON_PANEL);
    }
    ButtonPanelValue /= SamplesPerRead;
}

void ButtonHandler::clearDebounceTimers()
{
    LeftDebounceTimer = 0;
    MiddleDebounceTimer = 0;
    RightDebounceTimer = 0;
}
