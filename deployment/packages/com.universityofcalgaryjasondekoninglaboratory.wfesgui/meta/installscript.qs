/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    // constructor
}

Component.prototype.isDefault = function()
{
    // select the component by default
    return true;
}

Component.prototype.createOperations = function()
{
    try {
        // call the base create operations function
        component.createOperations();
		if (systemInfo.productType === "windows") {
			// Install Visual C++ Redistributable.
			component.addElevatedOperation("Execute", "{0,1602,1638,3010}", "@TargetDir@\\VC_redist.x64.exe", "/passive", "/norestart");
			// Add to Start Menu,
			component.addOperation("CreateShortcut", "@TargetDir@\\wfes-ui.exe", "@StartMenuDir@/wfes-ui.lnk", "iconPath=@TargetDir@\\icon.ico");
			// Add to Desktop.
			var userProfile = installer.environmentVariable("USERPROFILE");
            installer.setValue("UserProfile", userProfile);
            component.addOperation("CreateShortcut", "@TargetDir@\\wfes-ui.exe", "@UserProfile@\\Desktop\\wfes-ui.lnk");
		} else if (systemInfo.productType === "osx") {
			component.addElevatedOperation("CopyDirectory", "@TargetDir@/wfes-ui.app", "/Applications/");
		} else {
			// Copy .desktop file for showing application in menu
			component.addElevatedOperation("Copy", "@TargetDir@/WfesGui.desktop", "/usr/share/applications/");
		}
		
    } catch (e) {
        console.log(e);
    }
}
