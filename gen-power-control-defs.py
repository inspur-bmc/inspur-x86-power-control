#!/usr/bin/env python

import os
import sys
import yaml
from argparse import ArgumentParser
from mako.template import Template

tmpl = '''\
/* This is a generated file. */
#include "types.hpp"
#include <algorithm>
#include <vector>

namespace com
{
namespace inspur
{
namespace chassis
{
const std::vector<GpioDefinition> Gpios{
% for gpio in gpios:
    GpioDefinition{${gpio['key']},"${gpio['path']}","${gpio['name']}"},
% endfor
};
const GpioDefinition findGpioDefinition(const std::string& name)
{
    return *std::find_if(
               Gpios.cbegin(), Gpios.cend(),
               [&name](const auto& entry) { return name == std::get<labelField>(entry); });
}
} // namespace chassis
} // namespace inspur
} // namespace com
'''

if __name__ == '__main__':
    parser = ArgumentParser(description = "inspur-x86-power-control definition parser");

    parser.add_argument('-d','--gpiodefs_yaml',dest='gpiodefs_yaml',default='example/gpiodefs.yaml',
            help='gpio definitional yaml')
    parser.add_argument('-o','--output_dir',dest='output_dir',default='.',
            help='output directory')

    args = parser.parse_args()

    with open(args.gpiodefs_yaml,'r') as gpiodefs_input:
        gpiodefs_data = yaml.safe_load(gpiodefs_input) or {}

    output_file = os.path.join(args.output_dir,'gpiodefs.cpp')
    with open(output_file,'w') as output:
        output.write(Template(tmpl).render(gpios=gpiodefs_data))

