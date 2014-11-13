#include "marconetlist.h"
#include "schematic.h"
#include "wire.h"

#include <iostream>

namespace qucs {
namespace exports {

// --- MarcoNetlistConverter ---
QString
MarcoNetlistConverter::convertToMarcoNetlist(Schematic* schematic) {

    QString result = QString(   "# MarcoNetlist v0.1\n"
                                "# " + schematic->Frame_Text0 + "\n\n");

    result = result + "\n# Components:\n";
    // write down all components
    Component* component = schematic->Components->first();
    // TODO: enable C++11 usage of nullptr
    while(component != 0){

        int currentIndex = 0;

        QListIterator<Port*> portIterator(component->Ports);
        while(portIterator.hasNext()){
            Port* currentPort = portIterator.next();

            if(currentPort->Connection->Name.isEmpty()){
                currentPort->Connection->Name = component->Name + "_p" + QString::number(currentIndex);
            }
            currentIndex++;
        }

        result = result + component->convertToMarcoNetlist() + "\n";

        // next iteration
        component = schematic->Components->next();
    }

    result = result + "\n# Connections:\n";

    std::cerr << "Writing wires " << schematic->Wires->count() << std::endl;

    // write down all wires
    Wire* wire = schematic->Wires->first();
    // TODO: enable C++11 usage of nullptr

    int runningIndex = 0;
    while(wire != 0){
        // name the wire if not already done so...
        if((wire->Label == 0) || wire->Label->Name.isEmpty()){
            QString newName = QString("wire") + QString::number(runningIndex);
            wire->setName(newName,"0");
            runningIndex++;
            std::cerr << "New index: " << runningIndex << std::endl;
        }

        result = result + wire->convertToMarcoNetlist() + "\n";

        // next iteration
        wire = schematic->Wires->next();
    }
    return result;
}

} // end namespace exports
} // end namespace qucs
