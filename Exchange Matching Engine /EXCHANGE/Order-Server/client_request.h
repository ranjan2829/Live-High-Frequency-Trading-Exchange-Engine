#pragma once
#include <sstream>
#include "Exchange Matching Engine /Common Files/types.h"



#include "Exchange Matching Engine /Common Files/LockFreeQueues.h"
using namespace Common;
namespace Exchange {
#pragma pack(push, 1)
    enum class ClientRequestType : uint8_t {
        INVALID = 0,
        NEW = 1,
        CANCEL = 2
    };

    inline std::string clientRequestTypeToString(ClientRequestType type) {
        switch (type) {
            case ClientRequestType::NEW:
                return "NEW";
            case ClientRequestType::CANCEL:
                return "CANCEL";
            case ClientRequestType::INVALID:
                return "INVALID";
        }
        return "UNKNOWN";
    }
    struct MEClientRequest{
        ClientRequestType type_=ClientRequestType::INVALID;
        ClientId client_id =ClientId_INVALID;
        TickerId tickerId =TickerId_INVALID;
        OrderId orderId =OrderId_INVALID;
        Side side=Side::INVALID;
        Price price_=Price_INVALID;
        Qty qty_=Qty_INVALID;
        autp toString() const {
            std::stringstream ss;

        }


    };
}



