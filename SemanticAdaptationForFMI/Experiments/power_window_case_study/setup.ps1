Push-Location fmus\ThirdParty
	$fmus = Get-ChildItem | Where-Object {$_.Extension -eq ".fmu"} 
	ForEach ($fmu In $fmus){
		$fNameString = $fmu.BaseName
		7z x "$fNameString.fmu" -o".\$fNameString" -aoa
	}
Pop-Location
pause