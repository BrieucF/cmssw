#ifndef Phase2L1Trigger_DTTrigger_DTTrigPhase2Prod_cc
#define Phase2L1Trigger_DTTrigger_DTTrigPhase2Prod_cc
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "L1Trigger/DTPhase2Trigger/src/muonpath.h"
#include "L1Trigger/DTPhase2Trigger/src/analtypedefs.h"
#include "L1Trigger/DTPhase2Trigger/src/constants.h"

#include "L1Trigger/DTPhase2Trigger/interface/MotherGrouping.h"
#include "L1Trigger/DTPhase2Trigger/interface/InitialGrouping.h"

#include "CalibMuon/DTDigiSync/interface/DTTTrigBaseSync.h"
#include "CalibMuon/DTDigiSync/interface/DTTTrigSyncFactory.h"

#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/MuonDetId/interface/DTSuperLayerId.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"
#include "DataFormats/DTDigi/interface/DTDigiCollection.h"

#include "DQM/DTMonitorModule/interface/DTTrigGeomUtils.h"

//RPC TP
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"




#include <fstream>

#define MAX_VERT_ARRANG 4

class TFile;

class DTTrigPhase2Prod: public edm::EDProducer{
    typedef struct {
	bool latQValid;
	int  bxValue;
    } PARTIAL_LATQ_TYPE;
    typedef struct {
	bool valid;
	int bxValue;
	int invalidateHitIdx;
	MP_QUALITY quality;
    } LATQ_TYPE;

    struct metaPrimitive
    {
	uint32_t rawId;
	double t0;
	double x;
	double tanPhi;
	double phi;
	double phiB;
	double chi2;
	int quality;
	int wi1;
	int tdc1;
	int wi2;
	int tdc2;
	int wi3;
	int tdc3;
	int wi4;
	int tdc4;
	int wi5;
	int tdc5;
	int wi6;
	int tdc6;
	int wi7;
	int tdc7;
	int wi8;
	int tdc8;
    };

    typedef std::map< DTChamberId,DTDigiCollection,std::less<DTChamberId> > DTDigiMap;
    typedef DTDigiMap::iterator DTDigiMap_iterator;
    typedef DTDigiMap::const_iterator DTDigiMap_const_iterator;

 public:
    //! Constructor
    DTTrigPhase2Prod(const edm::ParameterSet& pset);
   
    //! Destructor
    ~DTTrigPhase2Prod() override;
    
    //! Create Trigger Units before starting event processing
    //void beginJob(const edm::EventSetup & iEventSetup);
    void beginRun(edm::Run const& iRun, const edm::EventSetup& iEventSetup) override;
  
    //! Producer: process every event and generates trigger data
    void produce(edm::Event & iEvent, const edm::EventSetup& iEventSetup) override;
    
    //! endRun: finish things
    void endRun(edm::Run const& iRun, const edm::EventSetup& iEventSetup) override;
    
    edm::ESHandle<DTGeometry> dtGeo;
    edm::ESHandle<RPCGeometry> rpcGeo;

    //plots
    TFile * theFileOut;
    
    TH1F * Nsegments;
    TH1F * NmetaPrimitives;
    TH1F * NfilteredMetaPrimitives;
    TH1F * NcorrelatedMetaPrimitives;
    TH1F * Ngroups;
    TH1F * Nquality;
    TH1F * Nquality_matched;
    TH1F * Nsegosl;
    TH1F * Nsegosl31;
    TH1F * Nmd;
    TH1F * Nmd31;
    TH2F * Nhits_segment_tp;
    
    TH1F * TIMEPhase2[5][4][14][10];
    TH1F * T0Phase2[5][4][14][10];

    TH2F * segment_vs_jm_x[5][4][14][10];
    TH1F * segment_vs_jm_x_gauss[5][4][14][10];

    TH2F * segment_vs_jm_tanPhi[5][4][14][10];
    TH1F * segment_vs_jm_tanPhi_gauss[5][4][14][10];
    
    TH2F * segment_vs_jm_T0[5][4][14][10];
    TH1F * segment_vs_jm_T0_gauss[5][4][14][10];
    TH1F * segment_vs_jm_T0_gauss_all[5][4][14][10];
    
    TH1F * expected_tanPsi[5][4][14];
    TH1F * observed_tanPsi[5][4][14][10];
    TH1F * all_observed_tanPsi[5][4][14][10];

    TH1F * expected_x[5][4][14];
    TH1F * observed_x[5][4][14][10];
    TH1F * all_observed_x[5][4][14][10];

    TH1F * expected_t0[5][4][14];
    TH1F * observed_t0[5][4][14][10];
    TH1F * all_observed_t0[5][4][14][10];
    
    TH1F * chi2[5][4][14][10];

    TH1F * TPphi[5][4][14][10];
    TH1F * TPphiB[5][4][14][10];

    TH2F * MP_x_back[5][4][14][10];
    TH2F * MP_psi_back[5][4][14][10];

    
    //ttrig
    std::string ttrig_filename;
    std::map<int,float> ttriginfo;

    //z
    std::string z_filename;
    std::map<int,float> zinfo;

    //shift
    std::string shift_filename;
    std::map<int,float> shiftinfo;

    int chosen_sl;

    std::vector<std::pair<int,MuonPath>> primitives;

    //JM
    // grouping
    void resetPrvTDCTStamp(void);
    bool isEqualComb2Previous(DTPrimitive *ptr[4]);
    void setInChannels(DTDigiCollection *digi, int sl);
    void selectInChannels(int baseCh);    
    bool notEnoughDataInChannels(void);
    //    std::vector<MuonPath> 
    void buildMuonPathCandidates(DTDigiCollection digis, std::vector<MuonPath*> *outMpath);
    void mixChannels(int sl, int pathId, std::vector<MuonPath*> *outMpath);

    void analyze(MuonPath *mPath,std::vector<metaPrimitive>& metaPrimitives,DTSuperLayerId dtSLId);

    int arePrimos(metaPrimitive primera, metaPrimitive segunda);
    int rango(metaPrimitive primera);
    bool outer(metaPrimitive primera);
    bool inner(metaPrimitive primera);
    void printmP(metaPrimitive mP);

    double trigPos(metaPrimitive mP);
    double trigDir(metaPrimitive mp);

    bool hasPosRF(int wh,int sec);

    double zcn[4];
    double xCenter[2];
    
    void setBXTolerance(int t);
    int getBXTolerance(void);

    void setChiSquareThreshold(float ch2Thr);
    
    void setMinimumQuality(MP_QUALITY q);
    MP_QUALITY getMinimumQuality(void);

    DTTrigGeomUtils *trigGeomUtils;


 private:
    // Trigger Configuration Manager CCB validity flag
    bool my_CCBValid;

    // BX offset used to correct DTTPG output
    int my_BXoffset;

    // Debug Flag
    bool debug;
    bool pinta;
    double tanPhiTh;
    double chi2Th;
    double dT0_correlate_TP;
    double min_dT0_match_segment;
    double minx_match_2digis;
    int min_phinhits_match_segment;
    bool do_correlation;
    int p2_df;
    bool filter_primos;

    //RPC
    bool useRPC;
    GlobalPoint getRPCGlobalPosition(RPCDetId rpcId, const RPCRecHit& rpcIt) const;

    // txt ttrig flag
    bool txt_ttrig_bc0;

    // ParameterSet
    edm::EDGetTokenT<DTRecSegment4DCollection> dt4DSegmentsToken;
    edm::EDGetTokenT<DTDigiCollection> dtDigisToken;
    edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;

    // for grouping 
    std::vector<DTPrimitive> muxInChannels[NUM_CELLS_PER_BLOCK];
    std::vector<DTPrimitive> channelIn[NUM_LAYERS][NUM_CH_PER_LAYER];
    std::vector<DTPrimitive> chInDummy;
    int prevTDCTimeStamps[4];
    int timeFromP1ToP2;
    int currentBaseChannel;
    
    Int_t grcode; // Grouping code
    
    float chiSquareThreshold;

    /* Combinaciones verticales de 3 celdas sobre las que se va a aplicar el
       mean-timer */
    static const int LAYER_ARRANGEMENTS[MAX_VERT_ARRANG][3];

    /* El máximo de combinaciones de lateralidad para 4 celdas es 16 grupos
       Es feo reservar todo el posible bloque de memoria de golpe, puesto que
       algunas combinaciones no serán válidas, desperdiciando parte de la
       memoria de forma innecesaria, pero la alternativa es complicar el
       código con vectores y reserva dinámica de memoria y, ¡bueno! ¡si hay
       que ir se va, pero ir p'a n'á es tontería! */
    LATERAL_CASES lateralities[16][4];
    LATQ_TYPE latQuality[16];

    int totalNumValLateralities;
    /* Posiciones horizontales de cada celda (una por capa), en unidades de
       semilongitud de celda, relativas a la celda de la capa inferior
       (capa 0). Pese a que la celda de la capa 0 siempre está en posición
       0 respecto de sí misma, se incluye en el array para que el código que
       hace el procesamiento sea más homogéneo y sencillo */
    int cellLayout[4];
    int bxTolerance;
    MP_QUALITY minQuality;

    void setCellLayout(const int layout[4]);
    void buildLateralities(void);
    bool isStraightPath(LATERAL_CASES sideComb[4]);

    /* Determina si los valores de 4 primitivas forman una trayectoria
       Los valores tienen que ir dispuestos en el orden de capa:
       0    -> Capa más próxima al centro del detector,
       1, 2 -> Siguientes capas
       3    -> Capa más externa */
    void evaluatePathQuality(MuonPath *mPath);
    void evaluateLateralQuality(int latIdx, MuonPath *mPath,
                                LATQ_TYPE *latQuality);
    /* Función que evalua, mediante el criterio de mean-timer, la bondad
       de una trayectoria. Involucra 3 celdas en 3 capas distintas, ordenadas
       de abajo arriba siguiendo el índice del array.
       Es decir:
            0-> valor temporal de la capa inferior,
            1-> valor temporal de la capa intermedia
            2-> valor temporal de la capa superior
       Internamente implementa diferentes funciones según el paso de la
       partícula dependiendo de la lateralidad por la que atraviesa cada
       celda (p. ej.: LLR => Left (inferior); Left (media); Right (superior))

       En FPGA debería aplicarse la combinación adecuada para cada caso,
       haciendo uso de funciones que generen el código en tiempo de síntesis,
       aunque la función software diseñada debería ser exportable directamente
       a VHDL */
    void validate(LATERAL_CASES sideComb[3], int layerIndex[3],
                  MuonPath* mPath, PARTIAL_LATQ_TYPE *latq);

    int eqMainBXTerm(LATERAL_CASES sideComb[2], int layerIdx[2],
                     MuonPath* mPath);

    int eqMainTerm(LATERAL_CASES sideComb[2], int layerIdx[2], MuonPath* mPath,
                   int bxValue);

    void getLateralCoeficients(LATERAL_CASES sideComb[2], int *coefs);
    bool sameBXValue(PARTIAL_LATQ_TYPE *latq);

    void calculatePathParameters(MuonPath *mPath);
    void calcTanPhiXPosChamber  (MuonPath *mPath);
    void calcCellDriftAndXcoor  (MuonPath *mPath);
    void calcChiSquare          (MuonPath *mPath);

    void calcTanPhiXPosChamber3Hits(MuonPath *mPath);
    void calcTanPhiXPosChamber4Hits(MuonPath *mPath);
    
    int getOmittedHit(int idx);

    int compute_pathId(MuonPath *mPath);
    
    
    // Grouping attributes and methods
    MotherGrouping* grouping_obj;
};


#endif

