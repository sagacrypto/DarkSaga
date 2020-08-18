// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2020 The DarkSaga developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500  ;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, Params().HashGenesisBlock() )
        (10000,   uint256("0xb63d4a092351a730e579f7b99b75b65161d87a6fe0adb3d8ceae0d02ba235687") )
        (20000,   uint256("0x0e2b47087bf6f365618651077c2069ed580a9a64a3fab23e030cf0122e9e12c3") )
        (30000,   uint256("0xbbf4f4ef827a391a58beaa7a64094d9a5d87b693c6d179097df0985e820159d7") )
        (40000,   uint256("0xbe67788837f1d21b383e002c96ea8936485c5ace5ee0eec024e6dc7decb66a03") )
        (50000,   uint256("0x0c8ca0a151cc90c9c44d9988a361fb2ef5626ebc5164edbf7c22d2a9fc77a008") )
        (60000,   uint256("0x79abfc1bff1eaabb214baf488c976aa63b90cd829fe8af7eb1d9970437868ea7") )
        (70000,   uint256("0x5f3ea4726779a923fa7b67b1f4781f306ab1dbedc3cd76dd4129b7a91a4cc0a5") )
        (100000,   uint256("0x20899a4d8484d42fb91fb2bafa7f2794248d3ddccae8b33d954a6cabb19c7f43") )
        (120000,   uint256("0xd4ff63f00b8bae4043f8bb9edd7a09dddb38fa51efe297fccdb71bdcf50b8904") )
        (215000,   uint256("0x758def70047fd5285b0802387bb3736826cf087b3bd53b45a479c18660db5b2b") )
        (945000,   uint256("0x25e7029182d0471d707142c21a63d622582ec797c7f8506669b35fe0371beb64") )
        (970000,   uint256("0xd701733ab4297a158fe2d2a8aa17eb7abc864d578252bf7d25e438d7a02cf5e0") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
