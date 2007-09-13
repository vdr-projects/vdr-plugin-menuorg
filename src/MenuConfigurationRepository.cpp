/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (C) 2007 Thomas Creutz, Tobias Grimm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 *
 */

#include "MenuConfigurationRepository.h"
#include <exception>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <libxml++/libxml++.h>
#include <glibmm/convert.h>
#include "SystemMenuNode.h"
#include "SubMenuNode.h"
#include "PluginMenuNode.h"
#include "CommandMenuNode.h"
#include "SeparatorMenuNode.h"
#include "XmlConfigurationFactory.h"

using namespace xmlpp;
using namespace std;

const string MenuConfigurationRepository::_dtd = 
  "<!ELEMENT menus ((menu | system | plugin | command | separator)+)>\n"
  "<!ELEMENT menu ((menu | system | plugin | command | separator)*)>\n"
  "<!ATTLIST menu name CDATA #REQUIRED>\n"
  "<!ELEMENT system EMPTY>\n"
  "<!ATTLIST system\n"
  " name CDATA #REQUIRED\n"
  " title CDATA #IMPLIED>\n"
  "<!ELEMENT plugin EMPTY>\n"
  "<!ATTLIST plugin\n"
  " name CDATA #REQUIRED\n"
  " title CDATA #IMPLIED>\n"
  "<!ELEMENT command EMPTY>\n"
  "<!ATTLIST command\n"
  " name CDATA #REQUIRED\n"
  " execute CDATA #REQUIRED\n"
  " confirm (yes|no) #IMPLIED>"
  "<!ELEMENT separator EMPTY>\n"
  "<!ATTLIST separator\n"
  " title CDATA #IMPLIED>\n";

MenuConfigurationRepository::MenuConfigurationRepository(string menuFileName)
{
    _configurationFileName = menuFileName;
    _cachedMenuConfiguration = NULL;
    _lastConfigFileModificationTime = 0;
}

MenuConfigurationRepository::~MenuConfigurationRepository()
{
    delete _cachedMenuConfiguration;
}

SubMenuNode* MenuConfigurationRepository::Load()
{ 
    if (ConfigFileHasBeenChange())
    {
        try
        {
            dsyslog("loading menuorg config file from %s", _configurationFileName.c_str()); 

            DomParser _parser;

            _parser.set_substitute_entities();
            _parser.parse_file(_configurationFileName);

            DtdValidator validator;
            validator.parse_memory(_dtd);

            Document *document = _parser.get_document();
            validator.validate( document );

            if (document)
            {
                _lastConfigFileModificationTime = CurrentConfigFileModificationTime();
                delete _cachedMenuConfiguration;
                _cachedMenuConfiguration = new SubMenuNode("root");
                CreateMenuTree(document->get_root_node(), _cachedMenuConfiguration);
            }

        }
        catch(const std::exception& ex)
        {
            cerr << "menuorg: Exception caught when parsing xml configuration: " << ex.what();
            esyslog("Exception caught when parsing xml configuration. See stderr output for details.");
        }        
    }
    return _cachedMenuConfiguration;
}

void MenuConfigurationRepository::Save(SubMenuNode& menuConfiguration)
{
    Document* doc = XmlConfigurationFactory::CreateXmlConfig(&menuConfiguration);
    doc->write_to_file_formatted(_configurationFileName);
}

bool MenuConfigurationRepository::ConfigFileHasBeenChange()
{
    return (CurrentConfigFileModificationTime() != _lastConfigFileModificationTime);  
}

time_t MenuConfigurationRepository::CurrentConfigFileModificationTime()
{
    struct stat fileState;
    if (stat(_configurationFileName.c_str(), &fileState) == 0)
    {
        return fileState.st_mtim.tv_sec;
    }
    return 0;
}

void MenuConfigurationRepository::CreateMenuTree(const Element* menuRoot, SubMenuNode* menuNode)
{
    Node::NodeList children = menuRoot->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {   
        const Element* childElement = dynamic_cast<const Element*>(*i);

        if (childElement)
        {
            string type = childElement->get_name();
            string name = GetAttributeValue(childElement, "name", "");

            if ( type == "menu")
            {
                SubMenuNode* subMenu = new SubMenuNode(name);
                subMenu->AddToParent(menuNode);
                CreateMenuTree(childElement, subMenu);
            }
            else if (type == "system")
            {
                menuNode->AddChild(new SystemMenuNode(VdrState::ByName(name), GetTitle(childElement, "")));
            }
            else if (type == "plugin")
            {
                menuNode->AddChild(new PluginMenuNode(name, GetTitle(childElement, "")));
            }
            else if (type == "command")
            {
                string execute = childElement->get_attribute("execute")->get_value();
                bool confirm = GetAttributeValue(childElement, "confirm", "false") == "yes";
                menuNode->AddChild(new CommandMenuNode(name, execute, confirm));
            }
            else if (type == "separator")
            {
                menuNode->AddChild(new SeparatorMenuNode(GetTitle(childElement, "")));
            }
        }
    }
}

string MenuConfigurationRepository::UnicodeToLocaleOrIso8859(Glib::ustring unicodeString)
{
    try
    {
        return Glib::locale_from_utf8(unicodeString);
    }
    catch (Glib::ConvertError)
    {
        return Glib::convert_with_fallback(unicodeString, "ISO8859-15", "UTF-8");
    }
}

string MenuConfigurationRepository::GetTitle(const Element* node, string defaultValue)
{
    return GetAttributeValue(node, "title", defaultValue);
}

string MenuConfigurationRepository::GetAttributeValue(const Element* node, string name, string defaultValue)
{
    const Attribute* attribute = node->get_attribute(name);
    return attribute ? (string) UnicodeToLocaleOrIso8859(attribute->get_value()) : defaultValue;
}
