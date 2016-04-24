/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2014 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __VIRTUALREFCANVAS_H__
#define __VIRTUALREFCANVAS_H__

#include <EditorHeaders.h>
#include <VisualizerWindowHeaders.h>
#include <VisualizerEditorHeaders.h>

#include "VirtualRef.h"

class ElectrodeTableButton;
class VirtualRefDisplay;

class VirtualRefCanvas : public Visualizer, public Button::Listener, public ComboBox::Listener, public Slider::Listener
{
public:

    VirtualRefCanvas(VirtualRef* n);
    ~VirtualRefCanvas();

	void paint(Graphics& g);

    void refresh();

	void beginAnimation();
    void endAnimation();

    void refreshState();
	void resized();

    void setParameter(int, float) {}
    void setParameter(int, int, int, float) {}

	void update();

    void buttonClicked(Button* button);

    void startRecording() { }
    void stopRecording() { }

	bool updateNeeded = false;

	void mouseDown(const MouseEvent& event);

	void comboBoxChanged(ComboBox* cb);
	void sliderValueChanged(Slider* slider);

private:

	ScopedPointer<VirtualRefDisplay> display;
	VirtualRef* processor;
	ScopedPointer<Viewport> displayViewport;

	ScopedPointer<ComboBox> presetNamesBox;
	ScopedPointer<Label> presetNamesLabel;
	ScopedPointer<ComboBox> channelCountBox;
	ScopedPointer<Label> channelCountLabel;
	StringArray presetNames;
	StringArray channelCounts;

	ScopedPointer<UtilityButton> resetButton;
	ScopedPointer<UtilityButton> selectModeButton;
	ScopedPointer<UtilityButton> saveButton;
	ScopedPointer<UtilityButton> loadButton;
	ScopedPointer<Slider> gainSlider;

	OwnedArray<ElectrodeTableButton> electrodeButtons;

	int scrollBarThickness;
	int scrollDistance;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualRefCanvas);

};


class ElectrodeTableButton : public ElectrodeButton
{
public:

	ElectrodeTableButton(int index, int rowIndex_, int colIndex_) : ElectrodeButton(index), rowIndex(rowIndex_), colIndex(colIndex_)
	{
	}

	int getRowIndex()
	{
		return rowIndex;
	}

	int getColIndex()
	{
		return colIndex;
	}

private:

	int rowIndex;
	int colIndex;

};


class CarButton : public ElectrodeButton
{
public:

	CarButton(String label_, int channelIndex_) : ElectrodeButton(channelIndex_)
	{
		setButtonText(label_);
	}
};


class VirtualRefDisplay : public Component, public Button::Listener, public KeyListener
{
public:

    VirtualRefDisplay(VirtualRef*, VirtualRefCanvas*, Viewport*, bool selectMode = false);
    ~VirtualRefDisplay();

    void paint(Graphics& g);

    void resized();
	void update();

    void mouseDown(const MouseEvent& event);

	void buttonEvent(Button* button);
	void buttonClicked(Button* button);

	bool keyPressed(const KeyPress &key, Component *originatingComponent);

	void drawTable();
	void reset();
	void setEnableSingleSelectionMode(bool b);

	void applyPreset(String name, int numChannels);

private:

    int nChannelsBefore;
	bool singleSelectMode;
	int selectedRow;
	int selectedColumn;

	VirtualRef* processor;
	VirtualRefCanvas* canvas;
    Viewport* viewport;
	ScopedPointer<Label> staticLabel;

	OwnedArray<ElectrodeTableButton> electrodeButtons;
	OwnedArray<CarButton> carButtons;
	OwnedArray<Label> rowLabels;
	OwnedArray<Label> headerLabels;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualRefDisplay);

};


#endif // __VIRTUALREFCANVAS_H__

