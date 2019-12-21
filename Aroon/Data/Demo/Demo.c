#region Using declarations
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Xml.Serialization;
using NinjaTrader.Cbi;
using NinjaTrader.Gui;
using NinjaTrader.Gui.Chart;
using NinjaTrader.Gui.SuperDom;
using NinjaTrader.Gui.Tools;
using NinjaTrader.Data;
using NinjaTrader.NinjaScript;
using NinjaTrader.Core.FloatingPoint;
using NinjaTrader.NinjaScript.Indicators;
using NinjaTrader.NinjaScript.DrawingTools;
#endregion

//This namespace holds Strategies in this folder and is required. Do not change it. 
namespace NinjaTrader.NinjaScript.Strategies
{
	public class DemoStrategy : Strategy
	{
		private AroonOscillator AroonOscillator1;
		private Bollinger Bollinger1;

		protected override void OnStateChange()
		{
			if (State == State.SetDefaults)
			{
				Description									= @"A test";
				Name										= "DemoStrategy";
				Calculate									= Calculate.OnPriceChange;
				EntriesPerDirection							= 1;
				EntryHandling								= EntryHandling.AllEntries;
				IsExitOnSessionCloseStrategy				= true;
				ExitOnSessionCloseSeconds					= 30;
				IsFillLimitOnTouch							= false;
				MaximumBarsLookBack							= MaximumBarsLookBack.TwoHundredFiftySix;
				OrderFillResolution							= OrderFillResolution.Standard;
				Slippage									= 0;
				StartBehavior								= StartBehavior.WaitUntilFlat;
				TimeInForce									= TimeInForce.Gtc;
				TraceOrders									= false;
				RealtimeErrorHandling						= RealtimeErrorHandling.StopCancelClose;
				StopTargetHandling							= StopTargetHandling.PerEntryExecution;
				BarsRequiredToTrade							= 20;
				// Disable this property for performance gains in Strategy Analyzer optimizations
				// See the Help Guide for additional information
				IsInstantiatedOnEachOptimizationIteration	= true;
			}
			else if (State == State.Configure)
			{
				AddDataSeries(Data.BarsPeriodType.Tick, 1);
			}
			else if (State == State.DataLoaded)
			{				
				AroonOscillator1				= AroonOscillator(Weighted, 14);
				Bollinger1				= Bollinger(Close, 2, 14);
				AroonOscillator1.Plots[0].Brush = Brushes.Goldenrod;
				Bollinger1.Plots[0].Brush = Brushes.Goldenrod;
				Bollinger1.Plots[1].Brush = Brushes.Goldenrod;
				Bollinger1.Plots[2].Brush = Brushes.Goldenrod;
				AddChartIndicator(AroonOscillator1);
				AddChartIndicator(Bollinger1);
				SetStopLoss("", CalculationMode.Currency, 2, true);
			}
		}

		protected override void OnBarUpdate()
		{
			if (BarsInProgress != 0) 
				return;

			if (CurrentBars[0] < 2)
				return;

			 // Set 1
			if (((Position.AveragePrice + ((GetCurrentAsk(0) + 1) ))  == AroonOscillator1[1])
				 && (Position.AveragePrice == Bollinger1.Lower[2]))
			{
			}
			
		}
	}
}
