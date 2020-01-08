import os
f = open("inc/currentPath.hh", 'w')
f.write("#ifndef TOPOLOGYPATH\n")
f.write("#define TOPOLOGYPATH \"" + os.path.abspath(os.curdir) + '"\n')
f.write("#endif\n\n")
