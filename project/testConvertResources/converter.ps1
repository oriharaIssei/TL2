
$files = Get-Item *.jpg

foreach ($file in $files) {
    Start-Process -FilePath TextureConverter.exe -ArgumentList $file -Wait
}

pause