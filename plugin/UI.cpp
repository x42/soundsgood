/*
 */

#include "DistrhoUI.hpp"

#include "widgets/InspectorWindow.hpp"
#include "widgets/Meter.hpp"

#include "Quanta.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class SoundsGoodUI : public UI
{
    static const uint kInitialWidth = 405;
    static const uint kInitialHeight = 256;

    ScopedPointer<InspectorWindow> inspectorWindow;

    Meter meter, meter2;

    QuantaTheme theme;
    QuantaKnob knob1, knob2, knob3;
    QuantaMixerSlider mslider;
    QuantaValueSlider slider1, slider2;

public:
    SoundsGoodUI()
        : UI(kInitialWidth, kInitialHeight),
          meter(this),
          meter2(this),
          knob1(this, theme),
          knob2(this, theme),
          knob3(this, theme),
          mslider(this, theme),
          slider1(this, theme),
          slider2(this, theme)
    {
        loadSharedResources();
        setGeometryConstraints(kInitialWidth, kInitialHeight, true);

        meter.setAbsolutePos(5, 5);
        meter.setName("My First Meter");
        meter.setSize(50, 200);

        meter2.setAbsolutePos(65, 5);
        meter2.setName("My Second Meter");
        meter2.setSize(50, 200);

        knob1.setAbsolutePos(120, 5);
        knob1.setName("Knob 1");
        knob1.setSize(36, 36);

        knob2.setAbsolutePos(200, 5);
        knob2.setName("Knob 2");
        knob2.setSize(36, 36);

        knob3.setAbsolutePos(250, 5);
        knob3.setName("Knob 3");
        knob3.setSize(36, 36);

        mslider.setAbsolutePos(160, 5);
        mslider.setName("Mixer Slider");
        mslider.setSize(28, 200);

        slider1.setAbsolutePos(220, 105);
        slider1.setName("Slider 1");
        slider1.setSize(72, 36);
        slider1.setRange(-90, 0);
        slider1.setBackgroundColor(Color::fromHTML("#585338"));
        slider1.setUnitLabel("dB");

        slider2.setAbsolutePos(220, 155);
        slider2.setName("Slider 2");
        slider2.setSize(72, 36);
        slider2.setRange(-100, 100);
        slider2.setValue(0);
        slider2.setUnitLabel("%");
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * DSP/Plugin Callbacks */

    void parameterChanged(uint32_t index, float value) override
    {
        switch (index)
        {
        case kParameter49:
            meter.setLeft(value);
            break;
        case kParameter50:
            meter.setRight(value);
            break;
        }
    }

   /* --------------------------------------------------------------------------------------------------------
    * DSP/Plugin Callbacks (optional) */

    void sampleRateChanged(double newSampleRate) override
    {
    }

   /* --------------------------------------------------------------------------------------------------------
    * Widget Callbacks */

    void onNanoDisplay() override
    {
        beginPath();
        rect(0, 0, getWidth(), getHeight());
        fillColor(theme.windowBackgroundColor);
        fill();

        fillColor(200, 200, 200);
        textAlign(ALIGN_RIGHT|ALIGN_TOP);

        textBox(getWidth()-100, 5, 90, "hi there!");
        textBox(getWidth()-200, 55, 190, "just testing some widgets, nevermind me");
    }

    bool onMouse(const MouseEvent& ev) override
    {
        if (UI::onMouse(ev))
            return true;

        if (ev.button == 1 && ev.press)
        {
            if (inspectorWindow == nullptr)
                inspectorWindow = new InspectorWindow(this);
            inspectorWindow->show();
        }

        return false;
    }

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundsGoodUI)
};

// -----------------------------------------------------------------------------------------------------------

UI* createUI()
{
    return new SoundsGoodUI();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
