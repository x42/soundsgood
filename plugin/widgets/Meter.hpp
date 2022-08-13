/*
 */

#pragma once

#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class Meter : public NanoSubWidget
{
    float fOutLeft = 0.25;
    float fOutRight = 0.5;
    Color fColor = Color(93, 231, 61);

public:
    explicit Meter(NanoTopLevelWidget* const w)
        : NanoSubWidget(w) {}

    void setLeft(const float left)
    {
        if (d_isNotEqual(fOutLeft, left))
        {
            fOutLeft = left;
            repaint();
        }
    }

    void setRight(const float right)
    {
        if (d_isNotEqual(fOutRight, right))
        {
            fOutRight = right;
            repaint();
        }
    }

protected:
    void onNanoDisplay() override
    {
        static const Color kColorBlack(0, 0, 0);
        static const Color kColorRed(255, 0, 0);
        static const Color kColorYellow(255, 255, 0);

        // get meter values
        const float outLeft = fOutLeft;
        const float outRight = fOutRight;

        // tell DSP side to reset meter values
        // setState("reset", "");

        // useful vars
        const float halfWidth        = static_cast<float>(getWidth())/2;
        const float redYellowHeight  = static_cast<float>(getHeight())*0.2f;
        const float yellowBaseHeight = static_cast<float>(getHeight())*0.4f;
        const float baseBaseHeight   = static_cast<float>(getHeight())*0.6f;

        // create gradients
        Paint fGradient1 = linearGradient(0.0f, 0.0f,            0.0f, redYellowHeight,  kColorRed,    kColorYellow);
        Paint fGradient2 = linearGradient(0.0f, redYellowHeight, 0.0f, yellowBaseHeight, kColorYellow, fColor);

        // paint left meter
        beginPath();
        rect(0.0f, 0.0f, halfWidth-1.0f, redYellowHeight);
        fillPaint(fGradient1);
        fill();
        closePath();

        beginPath();
        rect(0.0f, redYellowHeight-0.5f, halfWidth-1.0f, yellowBaseHeight);
        fillPaint(fGradient2);
        fill();
        closePath();

        beginPath();
        rect(0.0f, redYellowHeight+yellowBaseHeight-1.5f, halfWidth-1.0f, baseBaseHeight);
        fillColor(fColor);
        fill();
        closePath();

        // paint left black matching output level
        beginPath();
        rect(0.0f, 0.0f, halfWidth-1.0f, (1.0f-outLeft)*getHeight());
        fillColor(kColorBlack);
        fill();
        closePath();

        // paint right meter
        beginPath();
        rect(halfWidth+1.0f, 0.0f, halfWidth-2.0f, redYellowHeight);
        fillPaint(fGradient1);
        fill();
        closePath();

        beginPath();
        rect(halfWidth+1.0f, redYellowHeight-0.5f, halfWidth-2.0f, yellowBaseHeight);
        fillPaint(fGradient2);
        fill();
        closePath();

        beginPath();
        rect(halfWidth+1.0f, redYellowHeight+yellowBaseHeight-1.5f, halfWidth-2.0f, baseBaseHeight);
        fillColor(fColor);
        fill();
        closePath();

        // paint right black matching output level
        beginPath();
        rect(halfWidth+1.0f, 0.0f, halfWidth-2.0f, (1.0f-outRight)*getHeight());
        fillColor(kColorBlack);
        fill();
        closePath();
    }
};

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
