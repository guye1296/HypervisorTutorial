copy "HypervisorTutorial\" "C:\HypervisorTutorial\"

rem create a kernel service for the driver
sc create HypervisorTutorial binPath= C:\HypervisorTutorial\HypervisorTutorial.sys type= kernel

rem restart the kernel service

sc stop HypervisorTutorial
sc start HypervisorTutorial
