Description
-----------
This module adds some extra storage options for Webforms. You may choose to have the changes be holistic to all webforms across the site [`admin/config/content/webform`] or per-webform through each webform's **Form Settings** page [`node/{nid}/webform/configure`]. The purpose is to implement some field datum obfuscation when it just isn't enough to simply encrypt the information (look at the webform_encrypt module as an example [https://www.drupal.org/project/webform_encrypt]) in the backend. 

The assumption made with this module is that a privacy concern (institutional policy or lawful mandate) requires the enforcement of non-collection of private information (i.e.: names, birthdates, locations, etc.) Though it may be required to collect this information to initial create a profile, the information cannot be stored long term in the DB. Thus, this module enables a level of obfuscation of data during or after the submission process.

If the Rules module [https://www.drupal.org/project/rules] is included in your setup, it will expose some extra functionality to allow even further manipulation of the information. 

**N.B.**: At this time, the POST processing used by RULES allows the information to be stored in the DB temporarily such that RULES may be allowed to use the information before it is obfuscated. Once the RULES actions have been completed, and the proper conditions met and the correct actions applied, the information will be obfuscated from the DB tables. This is an inherent issue with how Drupal 7 Webforms work. Further work could be done to mitigate this step, but given budget constrictions at the time of module development, we could not push beyond this limit. 

The following components are included in those sort of post-processing:
* textarea
* textfield
* time
* date
* email
* select
* number
* boolean

The following component types not included: 
* <strong>fieldset</strong>
* <strong>file</strong>
* <strong>markup</strong>
* <strong>pagebreak</strong>
* <strong>grid</strong>
* <strong>hidden</strong>

Requests, Questions and Concerns
--------------------------------
Please post your component inclusion / exclusion requests in the issue queue on D.O.

Installation
------------
1) Place the module folder in your sites/all/modules folder
2) Make sure you have the webform module enabled
3) Activate the module via admin/build/modules

Usage
-----
As noted above, two settings pages will be made available for configuration of obfuscation options. A general webform approach at [`admin/config/content/webform`] or the more webform specific **Form Settings** page [`node/{nid}/webform/configure`]. In each case, the options are quite similar. You can enable the 