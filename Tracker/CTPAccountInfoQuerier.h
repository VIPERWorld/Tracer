#ifndef CTPACCOUNTINFOQUERIER_H
#define CTPACCOUNTINFOQUERIER_H

#include <memory>
#include <mutex>
#include <condition_variable>

#include <QMap>
#include <QList>

#include "ThostFtdcTraderApi.h"

#include "Account.h"
#include "Platform.h"

class CTPAccountInfoQuerier : public CThostFtdcTraderSpi
{
public:

    CTPAccountInfoQuerier(Account *pAccount);

    ~CTPAccountInfoQuerier();

public:

    void OnFrontConnected();

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast) ;

    void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

public:

    std::shared_ptr<AccountInfo> Query();

private:

    Account *m_pAccount;
    CThostFtdcTraderApi *m_pTradeApi;
    CThostFtdcTradingAccountField m_oTradingAccount;
    QList<CThostFtdcInstrumentField*> m_lInstruments;
    QMap<QString,CThostFtdcInstrumentMarginRateField*> m_lInstrumentMarginRates;
    QMap<QString,CThostFtdcInstrumentCommissionRateField*> m_lInstrumentCommissionRates;

    int m_nRequestNumber;
    CThostFtdcReqUserLoginField m_oLoginInfo;
    bool m_bCompleted;
    std::mutex m_lLock;
    std::condition_variable m_cWaitCondition;
    CThostFtdcQryInvestorField m_oQryInvestor;
    CThostFtdcQryTradingAccountField m_oQryTradingAccount;
    CThostFtdcQryInstrumentMarginRateField m_oQryInstrumentMarginRate;
    CThostFtdcQryInstrumentCommissionRateField m_oQryInstrumentCommissionRate;
    CThostFtdcQryInstrumentField m_oQryInstrument;
    CThostFtdcInvestorField m_oInvestor;
};

#endif // CTPACCOUNTINFOQUERIER_H