function changeColorEvent(event)
{
	var triggerObject = event.srcElement;
	document.getElementById('colorDiv').style.backgroundColor = triggerObject.innerHTMl.toLowerCase()
}
