// 
// // AddTaskGenRT
// 
AliAnalysisTask *AddTaskGenRT(TString suffixName =""){
  
  // Create the task, add it to manager and configure it
  //===========================================================================

  AliAnalysisTaskGenRT* taskSpectraLFMC = new  AliAnalysisTaskGenRT("AliAnalysisTaskPIDvsRT");
  
  taskSpectraLFMC->SetYRange(0.5);
  taskSpectraLFMC->IsXiAllowed(kFALSE);
  taskSpectraLFMC->SetMinPtLeading(5.0);
  taskSpectraLFMC->SetMaxPtLeading(40.0);
  
  // Get the pointer to the existing analysis manager via the static access method
  //===========================================================================

  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if(!mgr){ Printf("AliAnalysisTaskGenRT: No analysis manager to connect to."); return NULL; }

  // Check the analysis type using the event handlers connected to the analysis manager
  //===========================================================================

  if(!mgr->GetMCtruthEventHandler()){ Printf("AliAnalysisTaskGenRT: This task requires an input MC event handler."); return NULL; }

  // ADD the task
  //===========================================================================
  mgr -> AddTask(taskSpectraLFMC);  

  // Create containers for input/output

  TString finDirname	= "";
  TString inname	= "cinput";
  TString outBasic	= "cList";

  finDirname	+= suffixName.Data();
  inname	+= finDirname.Data();
  outBasic	+= finDirname.Data();

  
  // Input and Output Slots
  //===========================================================================

  TString outputfile = AliAnalysisManager::GetCommonFileName();
  outputfile += ":PWGLF_SimSpectraLF";
  
  AliAnalysisDataContainer *coutSim = mgr->CreateContainer(outBasic,TList::Class(),AliAnalysisManager::kOutputContainer,outputfile.Data());

  mgr->ConnectInput (taskSpectraLFMC, 0, mgr->GetCommonInputContainer());
  mgr->ConnectOutput(taskSpectraLFMC, 1, coutSim);
  
  return taskSpectraLFMC;
  
}

