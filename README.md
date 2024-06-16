# short-ex-trk
Code for the CMSDAS Schools Short Tracking Exercise

## The setup
This package is meant to provide solutions to the exercises 

* Setup in `CMSSW_14_0_9` 

```
scram p -n cmssw CMSSW_14_0_9
cd cmssw/src/
cmsenv
git clone https://gitlab.cern.ch/cmsdas-cern-2024/short-ex-trk.git -b master .
scram b -j 8
```

Then simply run the configs
```
cmsRun MyDirectory/PrintOutTracks/test/run_cfg.py
cmsRun MyDirectory/PrintOutTracks/test/run_cfg_MVA.py
cmsRun MyDirectory/PrintOutTracks/test/construct_secondary_vertices_cfg.py
```

or the scripts in 

`$CMSSW_BASE/src/MyDirectory/PrintOutTracks/scripts/`

----


