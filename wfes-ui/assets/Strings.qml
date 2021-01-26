pragma Singleton
import QtQuick 2.9

Item {
    // Window Title
        readonly property var wfes: qsTr("WFES")
        readonly property var wfesComplete: qsTr("Wright-Fisher Exact Solver")

    // Executables
        readonly property var wfesSingle: qsTr("WFES Single")
        readonly property var wfesSequential: qsTr("WFES Sequential")
        readonly property var wfesSweep: qsTr("WFES Sweep")
        readonly property var wfesSwitching: qsTr("WFES Switching")
        readonly property var wfafS: qsTr("WFAF-S")
        readonly property var wfafD: qsTr("WFAF-D")
        readonly property var timeDist: qsTr("Time Dist.")
        readonly property var phaseType: qsTr("Phase Type")

    // Bottom Bar
        readonly property var bottomBarStatus: qsTr("Status");
        readonly property var bottomBarNotExecuting: qsTr("Not executing.");
        readonly property var bottomBarExecutionTime: qsTr("Execution Time");
        readonly property var bottomBarZeroTime: qsTr("0.0s");

    // Upper Menu
        // Settings
        readonly property var upperMenuSettingsButton: qsTr("Settings")
        readonly property var upperMenuSaveConfigButton: qsTr("Save Config...")
        readonly property var upperMenuLoadConfigButton: qsTr("Load Config...")
        readonly property var upperMenuGenerateImagesCheckBox: qsTr("Generate Images")
        readonly property var upperMenuPopulationScaledCheckBox: qsTr("Population-Scaled")

        // Tooltips
        readonly property var upperMenuGenerateImagesCheckBoxTooltip: qsTr("Generate matrix/vector images.")
        readonly property var upperMenuPopulationScaledCheckBoxTooltip: qsTr("Use population-scaled parameters.")

        // View
        readonly property var upperMenuViewButton: qsTr("View")
        readonly property var upperMenuMatrixVisualizationButton: qsTr("Matrix Visualization")
        readonly property var upperMenuChartVisualizationButton: qsTr("Chart Visualization")

        // Windows
        readonly property var upperMenuWindowsButton: qsTr("Windows")
        readonly property var mainWindow: qsTr("Main Window")

        // Help
        readonly property var upperMenuHelpButton: qsTr("Help")
        readonly property var upperMenuManualButton: qsTr("Manual")
        readonly property var upperMenuAboutButton: qsTr("About")

    // Labels
        // Components
        readonly property var components: qsTr("Components")
        readonly property var commonParameters: qsTr("Common Parameters")

        // Mode
            readonly property var mode: qsTr("Mode")

            // Phase Type
                // Mode names
                readonly property var phaseTypeDist: qsTr("Phase Type Dist.")
                readonly property var phaseTypeMoments: qsTr("Phase Type Moments")

                // Tooltips
                readonly property var phaseTypeDistTooltip: qsTr("Calculate distribution of absorption times for a fixation-only model.")
                readonly property var phaseTypeMomentsTooltip: qsTr("Calculate moments of absorption times for a fixation-only model.")

            // Time Dist.
                // Mode names
                readonly property var timeDistMode: qsTr("Time Dist.")
                readonly property var timeDistSGV: qsTr("Time Dist. SGV")
                readonly property var timeDistSkip: qsTr("Time Dist. Skip")
                readonly property var timeDistDual: qsTr("Time Dist. Dual")

                // Tooltips
                readonly property var timeDistModeTooltip: qsTr("Distribution of time to fixation/extinction.")
                readonly property var timeDistSGVTooltip: qsTr("Time distribution of fixation with standing genetics variation.")
                readonly property var timeDistSkipTooltip: qsTr("Distribution of time to absorption, excluding mutation time.")
                readonly property var timeDistDualTooltip: qsTr("This calculates the distribution of time to fixation, extinction using a dual mutation model.")

            // Wfes Single
                // Mode names
                readonly property var wfesSingleAbsorption: qsTr("Absorption")
                readonly property var wfesSingleFixation: qsTr("Fixation")
                readonly property var wfesSingleEstablishment: qsTr("Establishment")
                readonly property var wfesSingleFundamental: qsTr("Fundamental")
                readonly property var wfesSingleNonAbsorbing: qsTr("Non Absorbing")
                readonly property var wfesSingleEquilibrium: qsTr("Equilibrium")
                readonly property var wfesSingleAlleleAge: qsTr("Allele Age")

                // Tooltips
                readonly property var wfesSingleAbsorptionTooltip: qsTr("Both fixation and extinction states are absorbing.")
                readonly property var wfesSingleFixationTooltip: qsTr("Only fixation state is absorbing.")
                readonly property var wfesSingleEstablishmentTooltip: qsTr("Calculate establishment properties.")
                readonly property var wfesSingleFundamentalTooltip: qsTr("Calculate the entire fundamental matrix (slow).")
                readonly property var wfesSingleNonAbsorbingTooltip: qsTr("Build a non-absorbing WF matrix.")
                readonly property var wfesSingleEquilibriumTooltip: qsTr("Calculate the equilibrium distribtion of allele states.")
                readonly property var wfesSingleAlleleAgeTooltip: qsTr("Calculate age of an allele.")

            // Wfes Sweep
                // Mode names
                readonly property var wfesSweepFixation: qsTr("Fixation")

                // Tooltips
                readonly property var wfesSweepFixationTooltip: qsTr("Only fixation state is absorbing.")

            // Wfes Switching
                // Mode names
                readonly property var wfesSwitchingAbsorption: qsTr("Absorption")
                readonly property var wfesSwitchingFixation: qsTr("Fixation")

                // Tooltips
                readonly property var wfesSwitchingAbsorptionTooltip: qsTr("Both fixation and extinction states are absorbing.")
                readonly property var wfesSwitchingFixationTooltip: qsTr("Only fixation state is absorbing.")


        // Population
            // Labels
            readonly property var population: qsTr("Population")
            readonly property var n: qsTr("N");
            readonly property var a: qsTr("a");
            readonly property var c: qsTr("c");
            readonly property var l: qsTr("l");
            readonly property var m: qsTr("m");
            readonly property var k: qsTr("k");
            readonly property var p: qsTr("p");
            readonly property var xObserved: qsTr("x");
            readonly property var kOdds: qsTr("k");
            readonly property var pStart: qsTr("p")
            readonly property var nSub: qsTr("N<sub>%1</sub>");
            readonly property var gSub: qsTr("G<sub>%1</sub>");
            readonly property var fSub: qsTr("F<sub>%1</sub>");
            readonly property var timeSub: qsTr("t<sub>%1</sub>");
            readonly property var pStartSub: qsTr("p<sub>%1</sub>");
            readonly property var rSub: qsTr("r<sub>%1</sub>");

            // Tooltips
            readonly property var nTooltip: qsTr("Size of the population in the Wright Fisher Model.")
            readonly property var aTooltip: qsTr("Tail truncation weight.")
            readonly property var cTooltip: qsTr("Integration cutoff.")
            readonly property var lTooltip: qsTr("Transition probability.")
            readonly property var mTooltip: qsTr("Maximum number of generations.")
            readonly property var kTooltip: qsTr("Number of Moments.")
            readonly property var gTooltip: qsTr("Number of generations for each epoch.")
            readonly property var fTooltip: qsTr("Approximating (down) factor for each population size.")
            readonly property var timeTooltip: qsTr("Expected time spent in each model.")
            readonly property var pTooltip: qsTr("Initial allele count.")
            readonly property var xObservedTooltip: qsTr("Observed number of copies (allele age only).")
            readonly property var kOddsTooltip: qsTr("Odds ratio (establishment only).")
            readonly property var pStartTooltip: qsTr("Starting probabilities.")
            readonly property var rTooltip: qsTr("Transition probability matrix between the WF component models.")

        // Mutation
            // Labels
            readonly property var mutation: qsTr("Mutation")
            readonly property var u: qsTr("u");
            readonly property var uScaled: qsTr("4Nu");
            readonly property var v: qsTr("v");
            readonly property var vScaled: qsTr("4Nv");
            readonly property var rMut: qsTr("r");
            readonly property var mMut: qsTr("m");
            readonly property var uSub: qsTr("u<sub>%1</sub>");
            readonly property var uSubScaled: qsTr("4Nu<sub>%1</sub>");
            readonly property var vSub: qsTr("v<sub>%1</sub>");
            readonly property var vSubScaled: qsTr("4Nv<sub>%1</sub>");
            readonly property var noProj: qsTr("No Proj.")

            // Tooltips
            readonly property var uTooltip: qsTr("Backward mutation rate.")
            readonly property var vTooltip: qsTr("Forward mutation rate.")
            readonly property var rMutTooltip: qsTr("No recurrent mutation.")
            readonly property var mMutTooltip: qsTr("No recurrent mutation.")
            readonly property var noProjTooltip: qsTr("Do not project the distribution down.")

        // Selection
            // Labels
            readonly property var selection: qsTr("Selection");
            readonly property var s: qsTr("s");
            readonly property var sScaled: qsTr("2Ns");
            readonly property var h: qsTr("h");
            readonly property var sSub: qsTr("s<sub>%1</sub>");
            readonly property var sSubScaled: qsTr("2Ns<sub>%1</sub>");
            readonly property var hSub: qsTr("h<sub>%1</sub>");

            // Tooltips
            readonly property var sTooltip: qsTr("Selection coefficient.")
            readonly property var hTooltip: qsTr("Dominance coefficient.")

        // Output Options
            // Labels
            readonly property var outputOptions: qsTr("Output Options")
            readonly property var outputQ: qsTr("Q")
            readonly property var outputR: qsTr("R")
            readonly property var outputP: qsTr("P")
            readonly property var outputN: qsTr("N")
            readonly property var outputNExt: qsTr("N<sub>Ext</sub>")
            readonly property var outputNFix: qsTr("N<sub>Fix</sub>")
            readonly property var outputNTmo: qsTr("N<sub>Tmo</sub>")
            readonly property var outputB: qsTr("B")
            readonly property var outputI: qsTr("I")
            readonly property var outputE: qsTr("E")
            readonly property var outputV: qsTr("V")
            readonly property var outputMoments: qsTr("Moments")
            readonly property var outputRes: qsTr("Res")
            readonly property var outputDist: qsTr("Dist")

            // Tooltips
            readonly property var outputQTooltip: qsTr("Output Q as CSV file.")
            readonly property var outputRTooltip: qsTr("Output R as CSV file.")
            readonly property var outputPTooltip: qsTr("Output P as CSV file.")
            readonly property var outputNTooltip: qsTr("Output N as CSV file.")
            readonly property var outputNExtTooltip: qsTr("Output Next (extinction-conditional sojourn) to file.")
            readonly property var outputNFixTooltip: qsTr("Output Nfix (fixation-conditional sojourn) to file.")
            readonly property var outputNTmoTooltip: qsTr("Output Ntmo (timeout-conditional sojourn) to file.")
            readonly property var outputBTooltip: qsTr("Output B as CSV file.")
            readonly property var outputITooltip: qsTr("Output I (Initial probability distribution) as CSV file.")
            readonly property var outputETooltip: qsTr("Output E (Equilibrium frequencies) as CSV file (Equilibrium mode only).")
            readonly property var outputVTooltip: qsTr("Output V (Variance time matrix) as CSV file (Fundamental mode only).")
            readonly property var outputMomentsTooltip: qsTr("Output Moments as CSV file.")
            readonly property var outputResTooltip: qsTr("Output Res (Generated results at right side) as CSV file.")
            readonly property var outputDistTooltip: qsTr("Output Allele freq. dist. as CSV file.")

        // Execution
            // Labels
            readonly property var execution: qsTr("Execution")
            readonly property var force: qsTr("Force")
            readonly property var t: qsTr("t")
            readonly property var sf: qsTr("Sf")
            readonly property var library: qsTr("Library")
            readonly property var solver: qsTr("Solver")
            readonly property var iDist: qsTr("I. Dist.")
            readonly property var stopButton: qsTr("Stop")
            readonly property var executeButton: qsTr("Execute")
            readonly property var searchButton: qsTr("Search")

            // Tooltips
            readonly property var forceTooltip: qsTr("Do not perform parameter checks.")
            readonly property var tTooltip: qsTr("Number of threads for OpenMP.")
            readonly property var sfTooltip: qsTr("Number of threads for OpenMP.")
            readonly property var libraryTooltip: qsTr("Library used for solving matrix systems.")
            readonly property var solverTooltip: qsTr("Solver used by viennacl.")
            readonly property var iDistTooltip: qsTr("Path to initial probability distribution CSV file.")

            // File dialog
            readonly property var iDistDialogTitle: qsTr("Please choose a csv file")

        // Output
            // Labels
            readonly property var output: qsTr("Output")
                // Phase Type
                readonly property var moments: qsTr("Moments")
                readonly property var mean: qsTr("Mean")
                readonly property var std: qsTr("Std")
                readonly property var meanTooltip: qsTr("Mean of the calculated moments.")
                readonly property var stdTooltip: qsTr("Standard deviation of the calculated moments.")

                // Wfaf-D and Wfaf-S
                readonly property var alleleFreqDist: qsTr("Allele freq. dist.")

                // Wfes
                readonly property var pExt: qsTr("P<sub>ext</sub>")
                readonly property var pExtTooltip: qsTr("Probability of extintion.")
                readonly property var pFix: qsTr("P<sub>fix</sub>")
                readonly property var pFixTooltip: qsTr("Probability of fixation.")
                readonly property var pTmo: qsTr("P<sub>tmo</sub>")
                readonly property var pTmoTooltip: qsTr("Probability of timeout.")
                readonly property var tAbs: qsTr("T<sub>abs</sub>")
                readonly property var tAbsTooltip: qsTr("Expected number of generations until absorption.")
                readonly property var tAbsStd: qsTr("T<sub>abs std</sub>")
                readonly property var tAbsStdTooltip: qsTr("Standard deviation of expected number of generations until absorption.")
                readonly property var tExt: qsTr("T<sub>ext</sub>")
                readonly property var tExtTooltip: qsTr("Expected number of generations until extinction.")
                readonly property var nExt: qsTr("N<sub>ext</sub>")
                readonly property var nExtTooltip: qsTr("Number of generations until extintion.")
                readonly property var tExtStd: qsTr("T<sub>ext std</sub>")
                readonly property var tExtStdTooltip: qsTr("Standard deviation of expected number of generations until extinction.")
                readonly property var tFix: qsTr("T<sub>fix</sub>")
                readonly property var tFixTooltip: qsTr("Expected number of generations until fixation.")
                readonly property var tFixStd: qsTr("T<sub>fix std</sub>")
                readonly property var tFixStdTooltip: qsTr("Standard deviation of expected number of generations until fixation.")
                readonly property var tTmo: qsTr("T<sub>tmo</sub>")
                readonly property var tTmoTooltip: qsTr("Expected number of generations until time out.")
                readonly property var tTmoStd: qsTr("T<sub>tmo std</sub>")
                readonly property var tTmoStdTooltip: qsTr("Standard deviation of expected number of generations until time out.")
                readonly property var rate: qsTr("Rate")
                readonly property var rateTooltip: qsTr("Rate of substitution.")
                readonly property var eFreqMut: qsTr("E[freq mut]")
                readonly property var eFreqMutTooltip: qsTr("Expected frequency of mutation.")
                readonly property var eFreqWt: qsTr("E[freq wt]")
                readonly property var eFreqWtTooltip: qsTr("One minus expected frequency of mutation.")
                readonly property var fEst: qsTr("F<sub>est</sub>")
                readonly property var fEstTooltip: qsTr("Frequency of establishment.")
                readonly property var pEst: qsTr("P<sub>est</sub>")
                readonly property var pEstTooltip: qsTr("Probability of establishment.")
                readonly property var tSeg: qsTr("T<sub>seg</sub>")
                readonly property var tSegTooltip: qsTr("Expected number of generations until segregation.")
                readonly property var tSegStd: qsTr("T<sub>seg std</sub>")
                readonly property var tSegStdTooltip: qsTr("Standard deviation of expected number of generations until segregation.")
                readonly property var tSegExt: qsTr("T<sub>seg ext</sub>")
                readonly property var tSegExtTooltip: qsTr("Expected number of generations until segregation (Extinction).")
                readonly property var tSegExtStd: qsTr("T<sub>seg ext std</sub>")
                readonly property var tSegExtStdTooltip: qsTr("Standard deviation of expected number of generations until segregation (Extinction).")
                readonly property var tSegFix: qsTr("T<sub>seg fix</sub>")
                readonly property var tSegFixTooltip: qsTr("Expected number of generations until segregation (Fixation).")
                readonly property var tSegFixStd: qsTr("T<sub>seg fix std</sub>")
                readonly property var tSegFixStdTooltip: qsTr("Standard deviation of expected number of generations until segregation (Fixation).")
                readonly property var tEst: qsTr("T<sub>est</sub>")
                readonly property var tEstTooltip: qsTr("Expected number of generations until establishment.")
                readonly property var tEstStd: qsTr("T<sub>est std</sub>")
                readonly property var tEstStdTooltip: qsTr("Standard deviation of expected number of generations until establishment.")
                readonly property var eA: qsTr("E(A)")
                readonly property var eATooltip: qsTr("Expectation of the allele age.")
                readonly property var sA: qsTr("S(A)")
                readonly property var sATooltip: qsTr("Standard deviation of the allele age.")




    // Links
    readonly property var gitHubWikiURL: qsTr("https://github.com/dekoning-lab/wfes-gui/wiki")

    // Generic
    readonly property string empty: ""
    readonly property var copyToClipboard: qsTr("Copy to Clipboard")
    readonly property string hyphen: " - "
    readonly property string endOfError: " \n \n"
    readonly property string colon: ": "
    readonly property string comp: "Comp. "
    readonly property var download: qsTr("Download")

    // Error messages
    readonly property var dialogWarning: qsTr("Warning")
    readonly property var incorrectInputParametersMessage: qsTr("Some input parameters are incorrect. The configuration cannot be saved until you fix those values.")
    readonly property var onCloseConfirmationMessage: qsTr("Some input parameters are incorrect. The configuration will be available in this session, but cannot be saved for future sessions until you fix those values. Do you want to exit anyway?")

    readonly property var nIsEmpty: qsTr("Population Size (N) is empty.")
    readonly property var nIsNotValid: qsTr("Population Size (N) is not a valid number.")
    readonly property var nIsSmall: qsTr("Population Size (N) is quite small, it must be at least 2.")
    readonly property var nIsLarge: qsTr("Population Size (N) is quite large, the computations will take a long time. Check 'Force' to ignore.")

    readonly property var aIsEmpty: qsTr("Tail Truncation Cutoff (a) is empty.")
    readonly property var aIsNotValid: qsTr("Tail Truncation Cutoff (a) is not a valid number.")
    readonly property var aIsSmall: qsTr("Tail Truncation Cutoff (a) is quite small. It must be at least 0.")
    readonly property var aIsLarge: qsTr("Tail Truncation Cutoff (a) value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore.")

    readonly property var cIsEmpty: qsTr("Integration Cutoff (c) is empty.")
    readonly property var cIsNotValid: qsTr("Integration Cutoff (c) is not a valid number.")
    readonly property var cIsSmall: qsTr("Integration Cutoff (c) is too small. It must be greater than 0.")
    readonly property var cIsLarge: qsTr("Integration Cutoff (c) is too large. The maximum value allowed is 1.")

    readonly property var pIsEmpty: qsTr("Initial Allele Count (p) is empty.")
    readonly property var pIsNotValid: qsTr("Initial Allele Count (p) is not a valid number.")
    readonly property var pIsSmall: qsTr("Initial Allele Count (p) is quite small. It must be at least 0.")
    readonly property var pIsLarge: qsTr("Initial Allele Count (p) value is quite high. The maximum value allowed is 2.")

    readonly property var pStartIsEmpty: qsTr("Starting copies (p) is empty.")
    readonly property var pStartIsNotValid: qsTr("Starting copies (p) is not a valid number.")
    readonly property var pStartIsSmall: qsTr("Starting copies (p) is quite small, if you want to disable it just use 0.")
    readonly property var pStartIsLargeAbsorption: qsTr("Starting Copies (p) is quite large. The maximum value allowed is 2N-1.")
    readonly property var pStartIsLargeFixation: qsTr("Starting Copies (p) is quite large. The maximum value allowed is 2N.")
    readonly property var pStartIsLargeFixationSweep: qsTr("Starting Copies (p) is quite large. The maximum value allowed is N.")
    readonly property var pStartIsLargeEstablishment: qsTr("Starting Copies (p) is quite large. The maximum value allowed is N-1.")
    readonly property var pStartIsLargeAlleleAge: qsTr("Starting Copies (p) is quite large. The maximum value allowed is 2N-1.")

    readonly property var xIsEmpty: qsTr("Observed copies (x) is empty.")
    readonly property var xIsNotValid: qsTr("Observed copies (x) is not a valid number.")
    readonly property var xIsSmall: qsTr("Observed copies (x) is quite small. It must be at least 1.")
    readonly property var xIsLarge: qsTr("Observed Copies (x) is quite large. The maximum value allowed is N.")

    readonly property var lIsEmpty: qsTr("Rate of Switching (l) is empty.")
    readonly property var lIsNotValid: qsTr("Rate of Switching (l) is not a valid number.")
    readonly property var lIsSmall: qsTr("Rate of Switching (l) is quite small. It must be at least 0.")
    readonly property var lIsLarge: qsTr("Rate of Switching (l) value is quite high. The maximum value allowed is 1.")

    readonly property var kOddsIsEmpty: qsTr("Odds ratio (k) is empty.")
    readonly property var kOddsIsNotValid: qsTr("Odds ratio (k) is not a valid number.")

    readonly property var mIsEmpty: qsTr("Maximum Number of Generations (m) is empty.")
    readonly property var mIsNotValid: qsTr("Maximum Number of Generations (m) is not a valid number.")
    readonly property var mIsSmall: qsTr("Maximum Number of Generations (m) is quite small, it must be at least 1.")
    readonly property var mIsLarge: qsTr("Maximum Number of Generations (m) is quite large, the computations will take a long time. Check 'Force' to ignore.")

    readonly property var kIsEmpty: qsTr("Number of Moments (k) is empty.")
    readonly property var kIsNotValid: qsTr("Number of Moments (k) is not a valid number.")
    readonly property var kIsSmall: qsTr("Number of Moments (k) is quite small, it must be at least 2.")

    readonly property var uIsEmpty: qsTr("Backward Mutation (u) is empty.")
    readonly property var uIsNotValid: qsTr("Backward Mutation (u) is not a valid number.")
    readonly property var uIsSmall: qsTr("Backward Mutation (u) is quite small. It must be at least 0.")
    readonly property var uIsLarge: qsTr("Backward Mutation (u) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")
    readonly property var uIsLargeScaled: qsTr("Backward Mutation (u) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")

    readonly property var vIsEmpty: qsTr("Forward Mutation (v) is empty.")
    readonly property var vIsNotValid: qsTr("Forward Mutation (v) is not a valid number.")
    readonly property var vIsSmall: qsTr("Forward Mutation (v) is quite small. It must be at least 0.")
    readonly property var vIsLarge: qsTr("Forward Mutation (v) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")
    readonly property var vIsLargeScaled: qsTr("Forward Mutation (v) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")

    readonly property var sIsEmpty: qsTr("Selection Coefficient (s) is empty.")
    readonly property var sIsNotValid: qsTr("Selection Coefficient (s) is not a valid number.")
    readonly property var sIsSmall: qsTr("Selection Coefficient (s) is quite small. It must be at least -2N.")
    readonly property var sIsLarge: qsTr("Selection Coefficient (s) is quite large. The maximum value allowed is 1.")
    readonly property var sIsLargeScaled: qsTr("Selection Coefficient (s) is quite large. The maximum value allowed is 2N.")

    readonly property var hIsEmpty: qsTr("Dominance Coefficient (h) is empty.")
    readonly property var hIsNotValid: qsTr("Dominance Coefficient (h) is not a valid number.")
    readonly property var hIsSmall: qsTr("Dominance Coefficient (h) is quite small. It must be at least 0.")
    readonly property var hIsLarge: qsTr("Dominance Coefficient (h) is quite large. The maximum value allowed is 1.")

    readonly property var tIsEmpty: qsTr("Number of Threads (t) is empty.")
    readonly property var tIsNotValid: qsTr("Number of Threads (t) is not a valid number.")
    readonly property var tIsSmall: qsTr("Number of Threads (t) is quite small, it must be at least 1.")

    readonly property var sfIsEmpty: qsTr("Sampling frequency (Sf) is empty.")
    readonly property var sfIsNotValid: qsTr("Sampling frequency (Sf) is not a valid number.")
    readonly property var sfIsSmall: qsTr("Sampling frequency (Sf) is quite small, it must be at least 1.")
    readonly property var sfIsLarge: qsTr("Sampling frequency (Sf) is quite large. The maximum value allowed is m.")

    readonly property var nMulIsEmpty: qsTr("Population Size (N%1) is empty.")
    readonly property var nMulIsNotValid: qsTr("Population Size (N%1) is not a valid number.")
    readonly property var nMulIsSmall: qsTr("Population Size (N%1) is quite small, it must be at least 2.")
    readonly property var nMulIsLarge: qsTr("Population Size (N%1) is quite large, the computations will take a long time. Check 'Force' to ignore.")

    readonly property var gMulIsEmpty: qsTr("Generations (G%1) is empty.")
    readonly property var gMulIsNotValid: qsTr("Generations (G%1) is not a valid number.")
    readonly property var gMulIsSmall: qsTr("Generations (G%1) is quite small, it must be at least 2.")

    readonly property var fMulIsEmpty: qsTr("Approximation Factor (f%1) is empty.")
    readonly property var fMulIsNotValid: qsTr("Approximation Factor (f%1) is not a valid number.")
    readonly property var fMulIsSmall: qsTr("Approximation Factor (f%1) is quite small, it must be at least 1.")
    readonly property var fMulIsLarge: qsTr("Approximation Factor (f%1) is quite large. The maximum value allowed is N.")

    readonly property var pStartMulIsEmpty: qsTr("Probability of starting (p%1) is empty.")
    readonly property var pStartMulIsNotValid: qsTr("Probability of starting (p%1) is not a valid number.")
    readonly property var pStartMulIsSmall: qsTr("Probability of starting (p%1) is quite small, it must be at least 2.")
    readonly property var pStartMulIsLarge: qsTr("Probability of starting (p%1) is quite large, the computations will take a long time. Check 'Force' to ignore.")
    readonly property var pStartMulDoesntAdd1: qsTr("Probabilities of starting (p) of all components must add to 1. The current sum is %1")

    readonly property var rSwitchMulIsEmpty: qsTr("Relative Probability of Switching (r%1) is empty.")
    readonly property var rSwitchMulIsNotValid: qsTr("Relative Probability of Switching (r%1) is not a valid number.")
    readonly property var rSwitchMulIsSmall: qsTr("Relative Probability of Switching (r%1) is quite small, it must be at least 0.")
    readonly property var rSwitchMulIsLarge: qsTr("Relative Probability of Switching (r%1) is quite large. The maximum value allowed is 1.")
    readonly property var rSwitchMulNumComps: qsTr("Relative Probability of Switching (r%1) has %2 components. It should have %3 components.")

    readonly property var tExpextedMulIsEmpty: qsTr("Expected Time (t%1) is empty.")
    readonly property var tExpextedMulIsNotValid: qsTr("Expected Time (t%1) is not a valid number.")
    readonly property var tExpextedMulIsSmall: qsTr("Expected Time (t%1) is quite small, it must be at least 2.")

    readonly property var uMulIsEmpty: qsTr("Backward Mutation (u%1) is empty.")
    readonly property var uMulIsNotValid: qsTr("Backward Mutation (u%1) is not a valid number.")
    readonly property var uMulIsSmall: qsTr("Backward Mutation (u%1) is quite small, it must be at least 0.")
    readonly property var uMulIsLargeScaled: qsTr("Backward Mutation (u%1) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")
    readonly property var uMulIsLarge: qsTr("Backward Mutation (u%1) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")

    readonly property var vMulIsEmpty: qsTr("Forward Mutation (v%1) is empty.")
    readonly property var vMulIsNotValid: qsTr("Forward Mutation (v%1) is not a valid number.")
    readonly property var vMulIsSmall: qsTr("Forward Mutation (v%1) is quite small, it must be at least 0.")
    readonly property var vMulIsLargeScaled: qsTr("Forward Mutation (v%1) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")
    readonly property var vMulIsLarge: qsTr("Forward Mutation (v%1) is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")

    readonly property var sMulIsEmpty: qsTr("Selection Coefficient (s%1) is empty.")
    readonly property var sMulIsNotValid: qsTr("Selection Coefficient (s%1) is not a valid number.")
    readonly property var sMulIsSmall: qsTr("Selection Coefficient (s%1) is quite negative. It must be at least -2N.")
    readonly property var sMulIsLargeScaled: qsTr("Forward Mutation (v%1) is quite large. The maximum value allowed is 1.")
    readonly property var sMulIsLarge: qsTr("Forward Mutation (v%1) is quite large. The maximum value allowed is 2N.")

    readonly property var hMulIsEmpty: qsTr("Dominance Coefficient (h%1) is empty.")
    readonly property var hMulIsNotValid: qsTr("Dominance Coefficient (h%1) is not a valid number.")
    readonly property var hMulIsSmall: qsTr("Dominance Coefficient (h%1) is quite small. It must be at least 0.")
    readonly property var hMulIsLarge: qsTr("Dominance Coefficient (h%1) is quite large. The maximum value allowed is 1.")

    readonly property var nSGVIsEmpty: qsTr("Population Size (N) of SGV is empty.")
    readonly property var nSGVIsNotValid: qsTr("Population Size (N) of SGV is not a valid number.")
    readonly property var nSGVIsSmall: qsTr("Population Size (N) of SGV is quite small, it must be at least 2.")
    readonly property var nSGVIsLarge: qsTr("Population Size (N) of SGV is quite large, the computations will take a long time. Check 'Force' to ignore.")

    readonly property var lSGVIsEmpty: qsTr("Rate of Switching to pre-adaptive phase (l) of SGV is empty.")
    readonly property var lSGVIsNotValid: qsTr("Rate of Switching to pre-adaptive phase (l) of SGV is not a valid number.")
    readonly property var lSGVIsSmall: qsTr("Rate of switching to pre-adaptive phase (l) of SGV is quite small. It must be at least 0.")
    readonly property var lSGVIsLarge: qsTr("Rate of switching to pre-adaptive phase (l) of SGV is quite large. The maximum value allowed is 10e-3.")

    readonly property var aSGVIsEmpty: qsTr("Tail Truncation Cutoff (a) of SGV is empty.")
    readonly property var aSGVIsNotValid: qsTr("Tail Truncation Cutoff (a) of SGV is not a valid number.")
    readonly property var aSGVIsSmall: qsTr("Tail Truncation Cutoff (a) of SGV is quite small. It must be at least 0.")
    readonly property var aSGVIsLarge: qsTr("Tail Truncation Cutoff (a) of SGV value is quite high. This might produce inaccurate results. A good value should be between 0 and 10e-10. Check 'Force' to ignore.")

    readonly property var cSGVIsEmpty: qsTr("Integration Cutoff (c) of SGV is empty.")
    readonly property var cSGVIsNotValid: qsTr("Integration Cutoff (c) of SGV is not a valid number.")
    readonly property var cSGVIsSmall: qsTr("Integration Cutoff (c) of SGV is too small. It must be greater than 0.")
    readonly property var cSGVIsLarge: qsTr("Integration Cutoff (c) of SGV is too large. The maximum value allowed is 1.")

    readonly property var mSGVIsEmpty: qsTr("Maximum Number of Generations (m) of SGV is empty.")
    readonly property var mSGVIsNotValid: qsTr("Maximum Number of Generations (m) of SGV is not a valid number.")
    readonly property var mSGVIsSmall: qsTr("Maximum Number of Generations (m) of SGV is quite small, it must be at least 1.")
    readonly property var mSGVIsLarge: qsTr("Maximum Number of Generations (m) of SGV is quite large, the computations will take a long time. Check 'Force' to ignore.")

    readonly property var uSGVisEmpty: qsTr("Backward Mutation (u%1) is empty.")
    readonly property var uSGVisNotValid: qsTr("Backward Mutation (u%1) of SGV is not a valid number.")
    readonly property var uSGVisSmall: qsTr("Backward Mutation (u%1) of SGV is quite small. It must be at least 0.")
    readonly property var uSGVisLarge: qsTr("Backward Mutation (u%1) of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")
    readonly property var uSGVisLargeScaled: qsTr("Backward Mutation (u%1) of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")

    readonly property var vSGVisEmpty: qsTr("Forward Mutation (v%1) is empty.")
    readonly property var vSGVisNotValid: qsTr("Forward Mutation (v%1) of SGV is not a valid number.")
    readonly property var vSGVisSmall: qsTr("Forward Mutation (v%1) of SGV is quite small. It must be at least 0.")
    readonly property var vSGVisLarge: qsTr("Forward Mutation (v%1) of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1/4N. Check 'Force' to ignore.")
    readonly property var vSGVisLargeScaled: qsTr("Forward Mutation (v%1) of SGV is quite large and might violate the Wright-Fisher assumptions. It should be less than 1. Check 'Force' to ignore.")

    readonly property var sSGVisEmpty: qsTr("Selection Coefficient (s%1) is empty.")
    readonly property var sSGVisNotValid: qsTr("Selection Coefficient (s%1) of SGV is not a valid number.")
    readonly property var sSGVisSmall: qsTr("Selection Coefficient (s%1) of SGV is quite negative. It must be at least -2N.")
    readonly property var sSGVisLarge: qsTr("Selection Coefficient (s%1) of SGV is quite large. The maximum value allowed is 1.")
    readonly property var sSGVisLargeScaled: qsTr("Selection Coefficient (s%1) of SGV is quite large. The maximum value allowed is 2N.")

    readonly property var hSGVisEmpty: qsTr("Dominance Coefficient (h%1) is empty.")
    readonly property var hSGVisNotValid: qsTr("Dominance Coefficient (h%1) of SGV is not a valid number.")
    readonly property var hSGVisSmall: qsTr("Dominance Coefficient (h%1) of SGV is quite small. It must be at least 0.")
    readonly property var hSGVisLarge: qsTr("Dominance Coefficient (h%1) of SGV is quite large. The maximum value allowed is 1.")

    // Charts
    readonly property var charts: qsTr("Charts")
    readonly property var nonGeneratedChart: qsTr("A chart will appear here when you execute an executable with Dist, Moments or Probs (P).")
    readonly property var data1: qsTr("Data ")
    readonly property var logScale: qsTr("Log Scale")
    readonly property var resetYAxis: qsTr("Reset Y Axis")
    readonly property var maxY: qsTr("Max. Y")
    readonly property var minY: qsTr("Min. Y")
}
