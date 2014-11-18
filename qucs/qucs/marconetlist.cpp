#include "marconetlist.h"
#include "schematic.h"
#include "wire.h"

#include <iostream>

namespace qucs {
namespace exports {

// --- MarcoNetlistConverter ---

QString
MarcoNetlistConverter::convertToMarcoNetlist(Schematic* schematic) {

    int currentIndex = 0;

    QString result = QString(   "# MarcoNetlist v0.1\n"
                                "# " + schematic->Frame_Text0 + "\n\n");

    result = result + "\n# Components:\n";

    // write down all components
    Component* component = schematic->Components->first();
    // TODO: enable C++11 usage of nullptr
    while(component != 0){

        currentIndex = 0;

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

    // generically name all nodes
    currentIndex = 0;
    for(Node* node = schematic->Nodes->first(); node != 0; node = schematic->Nodes->next()){
        if(node->Name != 0 && (!node->Name.isEmpty())){
            continue;
        }
        node->Name = QString("node_");
        node->Name += QString::number(currentIndex);
        currentIndex ++;
    }

    result = result + "\n# Connections:\n";
    // write down all wires

    // AFTER naming everything, iterate again to build netlist
    for(Wire* wire = schematic->Wires->first(); wire != 0; wire = schematic->Wires->next()){
        result = result + wire->convertToMarcoNetlist() + "\n";
    }

    return result;
}

} // end namespace exports
} // end namespace qucs
