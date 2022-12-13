from HiggsAnalysis.CombinedLimit.PhysicsModel import *

class HHtoTTbar(PhysicsModel):

    def getYieldScale(self,bin,process):
        if "_res" in process: return "signal_func"
        elif "_int_pos" in process: return "interference_func_pos"
        elif "_int_neg" in process: return "interference_func_neg"
        else:
            return 1

    def doParametersOfInterest(self):
        """Create POI and other parameters, and define the POI set."""
        self.modelBuilder.doVar("r[1,0,10]");
        self.modelBuilder.doSet("POI","r")

        self.modelBuilder.factory_("expr::signal_func(\"@0**4\",r)")
        self.modelBuilder.factory_("expr::interference_func_pos(\"@0**2\",r)")
        self.modelBuilder.factory_("expr::interference_func_neg(\"-(@0**2)\",r)")

hhtottbar = HHtoTTbar()

