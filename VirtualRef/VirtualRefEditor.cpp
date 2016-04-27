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


#include "VirtualRefEditor.h"
#include "VirtualRef.h"


VirtualRefEditor::VirtualRefEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : VisualizerEditor(parentNode, useDefaultParameterEditors), chanRefCanvas(nullptr)
{	
    tabText = "Virtual Ref";
    desiredWidth = 180;
}

VirtualRefEditor::~VirtualRefEditor()
{
	deleteAllChildren();
}

Visualizer* VirtualRefEditor::createNewCanvas()
{

    VirtualRef* processor = (VirtualRef*) getProcessor();
	chanRefCanvas = new VirtualRefCanvas(processor);
    return chanRefCanvas;
}

void VirtualRefEditor::updateSettings()
{
	if (chanRefCanvas != nullptr)
	{
		chanRefCanvas->update();
	}
}

void VirtualRefEditor::saveParametersDialog()
{
    if (!acquisitionIsActive)
    {
        FileChooser fc("Choose the file name...",
                       File::getCurrentWorkingDirectory(),
                       "*",
                       true);

        if (fc.browseForFileToSave(true))
        {
            File fileToSave = fc.getResult();

			XmlElement* xml = new XmlElement("SETTINGS");
			VirtualRef* p = dynamic_cast<VirtualRef*>(getProcessor());
			p->saveCustomParametersToXml(xml);
			if(!xml->writeToFile(fileToSave, String::empty))
			{
				CoreServices::sendStatusMessage("Couldn't save channel reference data to file.");
			}
			else
			{
				CoreServices::sendStatusMessage("Saved channel reference data to file " + fileToSave.getFullPathName());
			}
			delete xml;
        }
    } else
	{
		CoreServices::sendStatusMessage("Stop acquisition before saving channel references.");
    }
}

void VirtualRefEditor::loadParametersDialog()
{
    if (!acquisitionIsActive)
    {
        FileChooser fc("Choose the file name...",
                       File::getCurrentWorkingDirectory(),
                       "*",
                       true);

        if (fc.browseForFileToOpen())
        {
            File fileToOpen = fc.getResult();

			VirtualRef* p = dynamic_cast<VirtualRef*>(getProcessor());
			p->parametersAsXml = XmlDocument::parse(fileToOpen);
			p->loadCustomParametersFromXml();
			CoreServices::sendStatusMessage("Loaded channel reference data from file." + fileToOpen.getFullPathName());
			delete p->parametersAsXml;
        }
    } else
	{
		CoreServices::sendStatusMessage("Stop acquisition before loading channel references.");
    }
}

