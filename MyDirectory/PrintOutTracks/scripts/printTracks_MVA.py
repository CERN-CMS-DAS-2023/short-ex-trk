import DataFormats.FWLite as fwlite
events = fwlite.Events("/eos/user/c/cmsdas/2024/short-ex-trk/run321167_ZeroBias_AOD.root")
tracks = fwlite.Handle("std::vector<reco::Track>")
MVAs   = fwlite.Handle("std::vector<float>")

for i, event in enumerate(events):
    if i >= 5:
        break  # only the first 5 events                                                                                                                                                                   

    print("Event", i)
    event.getByLabel("generalTracks", tracks)
    event.getByLabel("generalTracks", "MVAValues", MVAs)

    numTotal = tracks.product().size()
    if numTotal == 0:
        continue

    numLoose = 0
    numTight = 0
    numHighPurity = 0

    for j, (track, mva) in enumerate(zip(tracks.product(), MVAs.product())):
        if track.quality(track.qualityByName("loose")):
            numLoose += 1
        if track.quality(track.qualityByName("tight")):
            numTight += 1
        if track.quality(track.qualityByName("highPurity")):
            numHighPurity += 1

        print("    Track", j, end=' ')
        print("\t charge/pT: {:.3f}".format(track.charge() / track.pt()), end=' ')
        print("\t phi: {:.3f}".format(track.phi()), end=' ')
        print("\t eta: {:.3f}".format(track.eta()), end=' ')
        print("\t dxy: {:.4f}".format(track.dxy()), end=' ')
        print("\t dz: {:.4f}".format(track.dz()), end=' ')
        print("\t nHits: {}".format(track.numberOfValidHits()), end=' ')
        print("({} P+ {} S)".format(track.hitPattern().numberOfValidPixelHits(), track.hitPattern().numberOfValidStripHits()), end=' ')
        print("\t algo: {}".format(track.algoName()), end=' ')
        print("\t mva: {:.3f}".format(mva))

    print("Event", i)
    print("numTotal:", numTotal, end=' ')
    print("numLoose:", numLoose, "({:.1f} %)".format(float(numLoose) / numTotal * 100), end=' ')
    print("numTight:", numTight, "({:.1f} %)".format(float(numTight) / numTotal * 100), end=' ')
    print("numHighPurity:", numHighPurity, "({:.1f} %)".format(float(numHighPurity) / numTotal * 100))
