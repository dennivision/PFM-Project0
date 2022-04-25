/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PFMProject0AudioProcessorEditor::PFMProject0AudioProcessorEditor (PFMProject0AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), cachedBgColor(audioProcessor.bgColor->get())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (400, 300);

    startTimerHz(20);
}

PFMProject0AudioProcessorEditor::~PFMProject0AudioProcessorEditor()
{
    if (audioProcessor.shouldPlaySound)
    {
        PFMProject0AudioProcessor::UpdateAutomatableParameter(audioProcessor.shouldPlaySound, false);
    }
}

void PFMProject0AudioProcessorEditor::timerCallback()
{
    update();
}

void PFMProject0AudioProcessorEditor::update()
{
    cachedBgColor = audioProcessor.bgColor->get();
    repaint();
}


//==============================================================================
void PFMProject0AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).interpolatedWith(juce::Colours::red, cachedBgColor));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PFMProject0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PFMProject0AudioProcessorEditor::mouseDown(const juce::MouseEvent& e)
{
    lastClickPos = e.getPosition();
}

void PFMProject0AudioProcessorEditor::mouseUp(const juce::MouseEvent& e)
{
    if (audioProcessor.shouldPlaySound)
    {
        //PFMProject0AudioProcessor::UpdateAutomatableParameter(audioProcessor.shouldPlaySound, !audioProcessor.shouldPlaySound->get());
    }
}

void PFMProject0AudioProcessorEditor::mouseDrag(const juce::MouseEvent& e)
{
    auto clickPos = e.getPosition();
    auto difY = juce::jlimit(-1.0, 1.0, -(clickPos.y - lastClickPos.y) / 200.0);
    difY = juce::jmap(difY, -1.0, 1.0, 0.0, 1.0);
    //auto difY = juce::jmap(static_cast<double>(clickPos.y - lastClickPos.y), 0.0, static_cast<double>(getHeight()), 1.0, 0.0);
    //DBG("difY:" << difY);

    PFMProject0AudioProcessor::UpdateAutomatableParameter(audioProcessor.bgColor, difY);

    update();
}

