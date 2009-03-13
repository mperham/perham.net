{*
 * $Revision: 15342 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <div class="giDescription">
    {g->text text="Windows XP comes with a nice feature that allows you to publish content from your desktop directly to a web service.  Follow the instructions below to enable this service on your Windows XP system."}

    <p>
      <b>{g->text text="Step 1"}</b><br>
      {g->text text="Download the configuration file using right-click 'Save Target As...'  Once downloaded, rename it to 'install_registry.reg'.  If it asks you for confirmation about changing the file type, answer 'yes'.  Right click on this file and you should see a menu appear.  Select the Merge option (this should be at the top of the menu).  It will ask you if you want to import these values into your registry.  Click 'Ok'.  It will tell you that the files were imported successfully.  Click 'Ok' again."}
      <br/>
      <a href="{g->url arg1="view=publishxp.DownloadRegistryFile"}">
        {g->text text="Download [install_registry.reg]"}
      </a>
    </p>
    <p>
      <b>{g->text text="Step 2"}</b><br>
      {g->text text="Open your Windows Explorer and browse to a folder containing supported images. Select the image(s) or a folder and there should be a link on the left that says 'Publish this file to the web...'  Click this link and then follow the instructions to log into your Gallery, select an album and publish the image."}
    </p>
  </div>
</div>
