import DataFormats.FWLite as fwlite
events = fwlite.Events("/eos/user/c/cmsdas/2024/short-ex-trk/run321167_ZeroBias_AOD.root")
tracks = fwlite.Handle("std::vector<reco::Track>")

for i, event in enumerate(events):
    if i >= 5: break # print info only about the first 5 events
    print("Event", i)
    event.getByLabel("generalTracks", tracks)
    for j, track in enumerate(tracks.product()):
        print(f"    Track {j}")
        print(f"\t charge/pT: {track.charge() / track.pt():.3f}")
        print(f"\t phi: {track.phi():.3f}")
        print(f"\t eta: {track.eta():.3f}")
        print(f"\t dxy: {track.dxy():.4f}")
        print(f"\t dz: {track.dz():.4f}")
