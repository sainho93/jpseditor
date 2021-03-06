/**
 * \file        jpscrossing.h
 * \date        Oct-01-2018
 * \version     v0.8.4
 * \copyright   <2009-2018> Forschungszentrum Jülich GmbH. All rights reserved.
 *
 * \section License
 * This file is part of JuPedSim.
 *
 * JuPedSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JuPedSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JuPedSim. If not, see <http://www.gnu.org/licenses/>.
 *
 * \section Description
 * This class is representing a door to another room in the building or to the outside.
 **/

#ifndef JPSCROSSING_H
#define JPSCROSSING_H

#include <QtWidgets>
#include <QtGui>
#include "src/jpsLineItem.h"
#include "src/jpszone.h"

class jpsCrossing
{
public:
    jpsCrossing(jpsLineItem *line);

    ~jpsCrossing(){}

    QList<JPSZone *> get_roomList();
    void addSubrooms(JPSZone* subroom1, JPSZone* subroom2 = nullptr);
    void setSubroom(JPSZone* subroom);
    void removeSubRoom(JPSZone* subroom);

    QString get_name();
    void change_name(QString name);
    int get_id();
    void set_id(int id);
    jpsLineItem *get_cLine();
    float get_elevation();
    void set_elevation(float elevation);
    QString getMaxAgents() const;
    void setMaxAgents(QString maxAgents);

    QString getOutflow() const;
    void setOutflow(QString outflow);

    bool isState() const;
    void setState(bool state);

private:
    QList<JPSZone *> relativeSubroom_list; // rooms that are relevant to the crossing, size can't more than 2!
    QString cName;
    jpsLineItem *cLine;
    int cId;
    float _elevation;
    bool state;
    QString max_agents;
    QString outflow;
};

#endif // JPSCROSSING_H
