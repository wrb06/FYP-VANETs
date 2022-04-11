//
// Copyright (C) 2006-2017 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package v2v_caching.simulations.veins_inet;

import inet.physicallayer.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import v2v_caching.veins_inet.VeinsInetCar;
import v2v_caching.veins_inet.VeinsInetManager;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsOsgVisualizer;

network Scenario
{
    @display("bgb=319,384");
    submodules:
        radioMedium: Ieee80211DimensionalRadioMedium {
            @display("p=10, 10");
        }
        manager: VeinsInetManager {
            @display("p=60, 10");
        }
        visualizer: IntegratedVisualizer {
            @display("p=110, 10");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=160, 10");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=210, 10");
        }
        roadsOsgVisualizer: RoadsOsgVisualizer {
            @display("p=260, 10");
        }
}
