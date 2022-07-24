#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);
    
    ConfigureAlgorithms();
}

AlgorithmManager::~AlgorithmManager()
{
    for(auto iter = algorithms.begin(); iter != algorithms.end(); ++iter)
    {
        delete iter->second;
    }
    delete factory;
    delete data;
}

bool AlgorithmManager::RunAll()
{
    // Run algorithms in defined order until the game is either won or lost
    data->Clear();
    grid->LeftClick(32 );
    grid->LeftClick(34 );
    grid->LeftClick(36 );
    grid->LeftClick(41 );
    grid->LeftClick(45 );
    grid->LeftClick(50 );
    grid->LeftClick(54 );
    grid->LeftClick(63 );
    grid->LeftClick(68 );
    grid->LeftClick(72 );
    grid->LeftClick(77 );
    grid->LeftClick(82 );
    grid->LeftClick(85 );
    grid->LeftClick(88 );
    grid->LeftClick(91 );
    grid->LeftClick(96 );
    grid->LeftClick(99 );
    grid->LeftClick(100);
    grid->LeftClick(104);
    grid->LeftClick(109);
    grid->LeftClick(113);
    grid->LeftClick(124);
    grid->LeftClick(132);
    grid->LeftClick(136);
    grid->LeftClick(141);
    grid->LeftClick(145);
    grid->LeftClick(147);
    grid->LeftClick(178);
    grid->LeftClick(182);
    grid->LeftClick(214);
    grid->LeftClick(236);
    grid->LeftClick(241);
    grid->LeftClick(268);
    grid->LeftClick(273);
    grid->LeftClick(296);
    grid->LeftClick(331);
    grid->LeftClick(340);
    grid->LeftClick(344);
    grid->LeftClick(348);
    grid->LeftClick(352);
    grid->LeftClick(354);
    grid->LeftClick(358);
    grid->LeftClick(362);
    grid->LeftClick(365);
    grid->LeftClick(367);
    grid->LeftClick(372);
    grid->LeftClick(376);
    grid->LeftClick(380);
    grid->LeftClick(386);
    grid->LeftClick(393);
    grid->LeftClick(399);
    grid->LeftClick(404);
    grid->LeftClick(408);
    grid->LeftClick(411);
    grid->LeftClick(414);
    grid->LeftClick(417);
    grid->LeftClick(421);
    grid->LeftClick(426);
    grid->LeftClick(431);
    grid->LeftClick(435);
    grid->LeftClick(439);
    grid->LeftClick(446);
    grid->PrintUncovered();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER]->Run();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS]->Run();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS]->Run();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS]->Run();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE]->Run();
    algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS]->Run();
    return true;
}

AlgorithmType AlgorithmManager::GetNextAlgorithm(const AlgorithmType previous_algorithm, const AlgorithmStatus previous_status)
{
    if(algorithm_transitions[previous_algorithm].count(previous_status) == 0)
    {
        throw std::invalid_argument("ERROR: AlgorithmManager::GetNextAlgorithm() unhandled AlgorithmStatus for this AlgorithmType!");
    }
    return algorithm_transitions[previous_algorithm][previous_status];
}

void AlgorithmManager::ConfigureAlgorithms()
{
    // This method is only called once in the constructor
    // It creates all Algorithm objects and defines the transitions between them
    // This is where changes can be made to the order of algorithm execution
    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithm_transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();

	algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY}
    };

	algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_BORDER] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_LAYER_ONE}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_ONE] = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_ONE] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SECTIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SECTIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_LAYER_TWO}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_TWO] = factory->Create(AlgorithmType::ALGORITHM_LAYER_TWO);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_TWO] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_FACE}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_FACE);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_FACE] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES}
    };

    algorithms[AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES] = factory->Create(AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES);
    algorithm_transitions[AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_SIMPLE_CORNERS}
    };

    algorithms[AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY] = factory->Create(AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY);
    algorithm_transitions[AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER}
    };
}
