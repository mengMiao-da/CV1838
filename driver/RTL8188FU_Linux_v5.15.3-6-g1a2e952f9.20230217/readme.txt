===============================================================================
		Software Package - Component
===============================================================================
	1. ReleaseNotes.pdf

	2. document/
		2.1. Driver_Configuration_for_RF_Regulatory_Certification.pdf
		2.2. How_to_append_vendor_specific_ie_to_driver_management_frames.pdf
		2.3. HowTo_enable_and_verify_TDLS_function_in_Wi-Fi_driver.pdf
		2.4. HowTo_enable_driver_to_support_80211d.pdf
		2.5. HowTo_enable_driver_to_support_mbo.pdf
		2.6. HowTo_enable_the_power_saving_functionality.pdf
		2.7. How_to_set_driver_debug_log_level.pdf
		2.8. HowTo_support_WIFI_certification_test.pdf
		2.9. linux_dhcp_server_notes.txt
		2.10. Miracast_for_Realtek_WiFi.pdf
		2.11. Quick_Start_Guide_for_Adaptivity_and_Carrier_Sensing_Test.pdf
		2.12. Quick_Start_Guide_for_Bridge.pdf
		2.13. Quick_Start_Guide_for_Driver_Compilation_and_Installation.pdf
		2.14. Quick_Start_Guide_for_SoftAP.pdf
		2.15. Quick_Start_Guide_for_Station_Mode.pdf
		2.16. Quick_Start_Guide_for_WOW.pdf
		2.17. Quick_Start_Guide_for_WPA3.pdf
		2.18. Quick_Start_Guide_for_wpa_supplicant_WiFi_P2P_test.pdf
		2.19. Realtek_WiFi_concurrent_mode_Introduction.pdf
		2.20. RTK_P2P_WFD_Programming_guide.pdf
		2.21. SoftAP_Mode_features.pdf
		2.22. Wireless_tools_porting_guide.pdf
		2.23. wpa_cli_with_wpa_supplicant.pdf

	3. driver/
		3.1. rtl8188FU_linux_v5.15.3-6-g1a2e952f9.20230217.tar.gz
			Naming rule: rtlCHIPS[_WiFi]_linux_vM.N.P[.H]-C-gSHA-1.yyyymmdd[_COEX_VER][_beta].tar.gz
			where:
				CHIPS: supported chips
				M: Major version
				N: miNor version
				P: Patch number
				H: Hotfix number
				C: numbers of commit
				SHA-1: sha-1 of this commit
				y: package year
				m: package month
				d: package day
				COEX_VER: Coext version
				_beta: beta driver

	4. android_ref_codes_JB_4.2/
		4.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		4.2. realtek_wifi_SDK_for_android_JB_4.2_20130208.tar.gz
			This tar ball includes our android wifi reference codes for Android 4.2

		4.3. Realtek_Wi-Fi_SDK_for_Android_JB_4.2.pdf
			Guide for porting Realtek wifi onto your Android 4.2 system

	5. android_ref_codes_KK_4.4/
		5.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		5.2. realtek_wifi_SDK_for_android_KK_4.4_20140117.tar.gz
			This tar ball includes our android wifi reference codes for Android 4.4

		5.3. Realtek_Wi-Fi_SDK_for_Android_KK_4.4.pdf
			Guide for porting Realtek wifi onto your Android 4.4 system

	6. android_ref_codes_L_5.x/
		6.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		6.2. realtek_wifi_SDK_for_android_L_5.x_20150811.tar.gz
			This tar ball includes our android wifi reference codes for Android 5.x

		6.3. Realtek_Wi-Fi_SDK_for_Android_L_5.x.pdf
			Guide for porting Realtek wifi onto your Android 5.x system

	7. android_ref_codes_M_6.x/
		7.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		7.2. realtek_wifi_SDK_for_android_M_6.x_20151116.tar.gz
			This tar ball includes our android wifi reference codes for Android 6.x

		7.3. Realtek_Wi-Fi_SDK_for_Android_M_6.x.pdf
			Guide for porting Realtek wifi onto your Android 6.x system

	8. android_ref_codes_N_7.0/
		8.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		8.2. realtek_wifi_SDK_for_android_N_7.0_20161024.tar.gz
			This tar ball includes our android wifi reference codes for Android 7.0

		8.3. Realtek_Wi-Fi_SDK_for_Android_N_7.0.pdf
			Guide for porting Realtek wifi onto your Android 7.0 system

	9. android_ref_codes_O_8.0/
		9.1. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		9.2. realtek_wifi_SDK_for_android_O_8.0_20200505.tar.gz
			This tar ball includes our android wifi reference codes for Android 8.0

		9.3. Realtek_Wi-Fi_SDK_for_Android_O_8.0.pdf
			Guide for porting Realtek wifi onto your Android 8.0 system

		9.4. supplicant_overlay_config.tar.gz

	10. android_ref_codes_P_9.x/
		10.1. wpa_supplicant_8_P_9.x_rtw_r29226.20180827.tar.gz
			wpa_supplicant_8 from Android 9.x SDK and patched by Realtek
			could be used Android 9.x. Support only cfg80211/nl80211.

		10.2. linux-3.0.42_STATION_INFO_ASSOC_REQ_IES.diff
			Kernel patch file for cfg80211's STATION_INFO_ASSOC_REQ_IES event for kernel 3.0.

		10.3. realtek_wifi_SDK_for_android_P_9.x_20200505.tar.gz
			This tar ball includes our android wifi reference codes for Android 9.x

		10.4. Realtek_Wi-Fi_SDK_for_Android_P_9.x.pdf
			Guide for porting Realtek wifi onto your Android 9.x system

		10.5. supplicant_overlay_config.tar.gz

		10.6. wpa_supplicant_8_P_9.x_rtw_add_support_for_self-managed_regulatory_device.tar.gz
			wpa_supplicant_8_P_9.x_rtw patches to add support for self-managed regulatory device.

	11. android_ref_codes_10.x/
		11.1. wpa_supplicant_8_10.x_rtw_29226.20200409.tar.gz
			wpa_supplicant_8 from Android 10.x SDK and patched by Realtek
			could be used Android 10.x. Support only cfg80211/nl80211.

		11.2. Realtek_Wi-Fi_SDK_for_Android_10.pdf
			Guide for porting Realtek wifi onto your Android 10.x system

		11.3. realtek_wifi_SDK_for_android_10_x_20200505.tar.gz
			This tar ball includes our android wifi reference codes for Android 10.x

		11.4. supplicant_overlay_config.tar.gz

	12. android_ref_codes_11.x/
		12.1. wpa_supplicant_8_11.0.0.r3_rtw_20201005.tar.gz
			wpa_supplicant_8 from Android 11.0 SDK and patched by Realtek
			could be used Android 11.0. Support only cfg80211/nl80211.

		12.2. Realtek_Wi-Fi_SDK_for_Android_11.pdf
			Guide for porting Realtek wifi onto your Android 11.0 system

		12.3. realtek_wifi_SDK_for_android_11_x_20210416.tar.gz
			This tar ball includes our android wifi reference codes for Android 11.0

		12.4. supplicant_overlay_config.tar.gz

		12.5. wpa_supplicant_8_11.0.0.r3_rtw_20201005.patch

	13. android_ref_codes_12.x/
		13.1. wpa_supplicant_8_android12-release_rtw_20211130.tar.gz
			wpa_supplicant_8 from Android 12.x SDK and patched by Realtek
			could be used Android 12.x. Support only cfg80211/nl80211.

		13.2. Realtek_Wi-Fi_SDK_for_Android_12.pdf
			Guide for porting Realtek wifi onto your Android 12.x system

		13.3. realtek_wifi_SDK_for_android_12_x_20211130.tar.gz
			This tar ball includes our android wifi reference codes for Android 12.x

		13.4. supplicant_overlay_config.tar.gz

	14. install.sh
		Script to compile and install WiFi driver easily in PC-Linux

	15. wireless_tools/
		15.1. wireless_tools.30.rtl.tar.gz

	16. wpa_supplicant_hostapd/
		16.1. wpa_supplicant_8_jb_4.2_rtw_r25670.20171213.tar.gz
			wpa_supplicant_8 from Android 4.2 SDK and patched by Realtek
			could be used for pure-linux and Android 4.2. Support only cfg80211/nl80211.

		16.2. wpa_supplicant_8_kk_4.4_rtw_r25669.20171213.tar.gz
			wpa_supplicant_8 from Android 4.4 SDK and patched by Realtek
			could be used for pure-linux and Android 4.4. Support only cfg80211/nl80211.

		16.3. wpa_supplicant_8_L_5.x_rtw_r24600.20171025.tar.gz
			wpa_supplicant_8 from Android 5.x SDK and patched by Realtek
			could be used for pure-linux and Android 5.x. Support only cfg80211/nl80211.

		16.4. wpa_supplicant_8_M_6.x_rtw_r24570.20171025.tar.gz
			wpa_supplicant_8 from Android 6.x SDK and patched by Realtek
			could be used for pure-linux and Android 6.x. Support only cfg80211/nl80211.

		16.5. wpa_supplicant_8_N_7.x_rtw_r24577.20171025.tar.gz
			wpa_supplicant_8 from Android 7.x SDK and patched by Realtek
			could be used for pure-linux and Android 7.x. Support only cfg80211/nl80211.

		16.6. wpa_supplicant_8_O_8.x_rtw-17-g894b400ab.20210716.tar.gz
			wpa_supplicant_8 from Android 8.x SDK and patched by Realtek
			could be used for pure-linux and Android 8.x. Support only cfg80211/nl80211.

		16.7. concurrent_mode_p2p_hostapd.conf

		16.8. concurrent_mode_wpa_0_8.conf

		16.9. hostap_2_10-rtw-9-g422792039.20220120.tar.gz
			This package includes w1.fi official wpa_supplicant and hostapd, and it is patched by Realtek.
			It can be used for pure Linux, which only supports cfg80211/nl80211.

		16.10. p2p_hostapd.conf
			Configure file for hostapd for Wi-Fi Direct (P2P)

		16.11. rtl_hostapd_2G.conf
			Configure files for Soft-AP mode 2.4G

		16.12. rtl_hostapd_5G.conf
			Configure files for Soft-AP mode 5G

		16.13. rtl_hostapd_6G.conf
			Configure files for Soft-AP mode 6G

		16.14. wpa_0_8.conf
			Configure file sample for wpa_supplicant-0.8

		16.15. wpa_supplicant-0.6.9_wps_patch_20100201_1.tar.gz

		16.16. wpa_supplicant_hostapd-0.8_rtw-2-ga8ef7c824.20200911.tar.gz
			16.16.1 wpa_supplicant
				The tool help the wlan network to communicate under the
				protection of WPAPSK mechanism (WPA/WPA2) and add WPS patch

			16.16.2 hostapd

==================================================================================================================
		User Guide for Driver compilation and installation
==================================================================================================================
			(*) Please refer to document/Quick_Start_Guide_for_Driver_Compilation_and_Installation.pdf
==================================================================================================================
		User Guide for Station mode
==================================================================================================================
			(*) Please refer to document/Quick_Start_Guide_for_Station_Mode.pdf
==================================================================================================================
		User Guide for Soft-AP mode
==================================================================================================================
			(*) Please refer to document/Quick_Start_Guide_for_SoftAP.pdf
			(*) Please use hostap_2_10-rtw-9-g422792039.20220120.tar.gz
			(*) Please refer to document/linux_dhcp_server_notes.txt
==================================================================================================================
		User Guide for Wi-Fi Direct
==================================================================================================================
		Realtek Legacy Wi-Fi Direct:
			(*) Please refer to document/RTK_P2P_WFD_Programming_guide.pdf
			(*) Please use wpa_supplicant_hostapd-0.8_rtw-2-ga8ef7c824.20200911.tar.gz
			(*) Please refer to document/linux_dhcp_server_notes.txt
		Wi-Fi Direct with nl80211
			(*) Please use:
					wpa_supplicant_8_jb_4.2_rtw_r25670.20171213.tar.gz
				or
					wpa_supplicant_8_kk_4.4_rtw_r25669.20171213.tar.gz
				or
					wpa_supplicant_8_L_5.x_rtw_r24600.20171025.tar.gz
				or
					wpa_supplicant_8_M_6.x_rtw_r24570.20171025.tar.gz
				or
					wpa_supplicant_8_N_7.x_rtw_r24577.20171025.tar.gz
				or
					wpa_supplicant_8_O_8.x_rtw-17-g894b400ab.20210716.tar.gz
				or
					wpa_supplicant_8_P_9.x_rtw_r29226.20180827.tar.gz
				or
					wpa_supplicant_8_10.x_rtw_29226.20200409.tar.gz
				or
					wpa_supplicant_8_11.0.0.r3_rtw_20201005.tar.gz
				or
					wpa_supplicant_8_android12-release_rtw_20211130.tar.gz
			(*) For P2P instruction/command, please refer to:
					README-P2P inside the wpa_supplicant folder of the wpa_supplicant_8 you choose
			(*) For DHCP server, please refer to:
					document/linux_dhcp_server_notes.txt
==================================================================================================================
		User Guide for WPS2.0
==================================================================================================================
			(*) Please use:
					hostap_2_10-rtw-9-g422792039.20220120.tar.gz
				or
					wpa_supplicant_8_jb_4.2_rtw_r25670.20171213.tar.gz
				or
					wpa_supplicant_8_kk_4.4_rtw_r25669.20171213.tar.gz
				or
					wpa_supplicant_8_L_5.x_rtw_r24600.20171025.tar.gz
				or
					wpa_supplicant_8_M_6.x_rtw_r24570.20171025.tar.gz
				or
					wpa_supplicant_8_N_7.x_rtw_r24577.20171025.tar.gz
				or
					wpa_supplicant_8_O_8.x_rtw-17-g894b400ab.20210716.tar.gz
				or
					wpa_supplicant_8_P_9.x_rtw_r29226.20180827.tar.gz
				or
					wpa_supplicant_8_10.x_rtw_29226.20200409.tar.gz
				or
					wpa_supplicant_8_11.0.0.r3_rtw_20201005.tar.gz
				or
					wpa_supplicant_8_android12-release_rtw_20211130.tar.gz
			(*) For WPS instruction/command, please refert to:
					README-WPS inside the wpa_supplicant folder of the wpa_supplicant_8 you choose
==================================================================================================================
		User Guide for Power Saving Mode
==================================================================================================================
			(*) Please refer to document/HowTo_enable_the_power_saving_functionality.pdf
==================================================================================================================
		User Guide for Applying Wi-Fi solution onto Andriod System
==================================================================================================================
			(*) For Android 4.2, please refer to android_ref_codes_JB_4.2/Realtek_Wi-Fi_SDK_for_Android_JB_4.2.pdf
			(*) For Android 4.4, please refer to android_ref_codes_KK_4.4/Realtek_Wi-Fi_SDK_for_Android_KK_4.4.pdf
			(*) For Android 5.x, please refer to android_ref_codes_L_5.x/Realtek_Wi-Fi_SDK_for_Android_L_5.x.pdf
			(*) For Android 6.x, please refer to android_ref_codes_M_6.x/Realtek_Wi-Fi_SDK_for_Android_M_6.x.pdf
			(*) For Android 7.0, please refer to android_ref_codes_N_7.0/Realtek_Wi-Fi_SDK_for_Android_N_7.0.pdf
			(*) For Android 8.0, please refer to android_ref_codes_O_8.0/Realtek_Wi-Fi_SDK_for_Android_O_8.0.pdf
			(*) For Android 9.x, please refer to android_ref_codes_P_9.x/Realtek_Wi-Fi_SDK_for_Android_P_9.x.pdf
			(*) For Android 10.x, please refer to android_ref_codes_10.x/Realtek_Wi-Fi_SDK_for_Android_10.pdf
			(*) For Android 11.0, please refer to android_ref_codes_11.x/Realtek_Wi-Fi_SDK_for_Android_11.pdf
			(*) For Android 12.x, please refer to android_ref_codes_12.x/Realtek_Wi-Fi_SDK_for_Android_12.pdf
==================================================================================================================
		User Guide for WPA3 Personal
==================================================================================================================
			(*) hostap_2_10-rtw-9-g422792039.20220120.tar.gz
			(*) Please refer to wpa_cli_with_wpa_supplicant.pdf
			(*) Please refer to Quick_Start_Guide_for_WPA3.pdf
